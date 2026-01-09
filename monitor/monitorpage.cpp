/**
 * @file monitorpage.cpp
 * @brief 实时监控页面实现
 *
 * 本文件实现了实时监控页面的所有功能，包括设备选择、
 * 轮询控制、数据显示等。
 */

#include "monitorpage.h"
#include "../common/appstyle.h"
#include "../common/toast.h"
#include "../service/deviceservice.h"
#include "../service/modbusservice.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>

MonitorPage::MonitorPage(QWidget *parent)
    : QWidget(parent)
    , m_titleBar(nullptr)
    , m_backBtn(nullptr)
    , m_titleLabel(nullptr)
    , m_deviceCombo(nullptr)
    , m_startStopBtn(nullptr)
    , m_statusLed(nullptr)
    , m_statusLabel(nullptr)
    , m_table(nullptr)
    , m_pollTimer(new QTimer(this))
    , m_isPolling(false)
    , m_currentDeviceId(-1)
{
    setupUI();
    loadDevices();

    connect(m_pollTimer, &QTimer::timeout, this, &MonitorPage::onPollTimer);
}

MonitorPage::~MonitorPage()
{
    if (m_isPolling) {
        ModbusService::stopPolling(m_currentDeviceId);
    }
}

void MonitorPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    setupTitleBar();
    mainLayout->addWidget(m_titleBar);

    // Content area
    QWidget *content = new QWidget(this);
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(10, 8, 10, 8);
    contentLayout->setSpacing(8);

    setupControls();
    contentLayout->addWidget(m_deviceCombo->parentWidget());

    setupTable();
    contentLayout->addWidget(m_table, 1);

    mainLayout->addWidget(content, 1);
}

void MonitorPage::setupTitleBar()
{
    m_titleBar = new QWidget(this);
    m_titleBar->setFixedHeight(40);
    m_titleBar->setStyleSheet("background-color: #0f3460;");

    QHBoxLayout *layout = new QHBoxLayout(m_titleBar);
    layout->setContentsMargins(5, 0, 10, 0);
    layout->setSpacing(10);

    m_backBtn = new QPushButton("<", m_titleBar);
    m_backBtn->setFixedSize(40, 36);
    m_backBtn->setStyleSheet(
        "QPushButton { background-color: transparent; color: #ffffff; font-size: 18pt; border: none; }"
        "QPushButton:pressed { background-color: #e94560; }"
    );
    connect(m_backBtn, &QPushButton::clicked, this, &MonitorPage::goBack);
    layout->addWidget(m_backBtn);

    m_titleLabel = new QLabel("实时监控", m_titleBar);
    m_titleLabel->setStyleSheet("color: #ffffff; font-size: 16pt; font-weight: bold;");
    layout->addWidget(m_titleLabel);

    layout->addStretch();
}

void MonitorPage::setupControls()
{
    QWidget *controlWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(controlWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    // 设备选择器
    m_deviceCombo = new QComboBox(controlWidget);
    m_deviceCombo->setStyleSheet(AppStyle::getInputStyle());
    m_deviceCombo->setMinimumWidth(180);
    connect(m_deviceCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MonitorPage::onDeviceChanged);
    layout->addWidget(m_deviceCombo);

    layout->addStretch();

    // 状态指示灯
    m_statusLed = new QLabel(controlWidget);
    m_statusLed->setFixedSize(16, 16);
    m_statusLed->setStyleSheet(
        "background-color: #606060; border-radius: 8px;"
    );
    layout->addWidget(m_statusLed);

    // 状态标签
    m_statusLabel = new QLabel("已停止", controlWidget);
    m_statusLabel->setStyleSheet("color: #a0a0a0; font-size: 11pt;");
    layout->addWidget(m_statusLabel);

    // 启动/停止按钮
    m_startStopBtn = new QPushButton("启动", controlWidget);
    m_startStopBtn->setStyleSheet(AppStyle::getButtonStyle(true));
    m_startStopBtn->setMinimumWidth(80);
    m_startStopBtn->setMinimumHeight(40);
    connect(m_startStopBtn, &QPushButton::clicked, this, &MonitorPage::onStartStopClicked);
    layout->addWidget(m_startStopBtn);
}

void MonitorPage::setupTable()
{
    m_table = new QTableWidget(this);
    m_table->setColumnCount(4);
    m_table->setHorizontalHeaderLabels(QStringList() << "地址" << "名称" << "值" << "时间");
    m_table->setStyleSheet(AppStyle::getTableStyle());
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->verticalHeader()->setVisible(false);
    m_table->setShowGrid(false);

    // 列宽
    m_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    m_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    m_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    m_table->setColumnWidth(0, 50);
    m_table->setColumnWidth(2, 100);
    m_table->setColumnWidth(3, 80);

    m_table->verticalHeader()->setDefaultSectionSize(32);

    connect(m_table, &QTableWidget::cellDoubleClicked,
            this, &MonitorPage::onTableDoubleClicked);
}

void MonitorPage::loadDevices()
{
    m_deviceCombo->clear();
    m_deviceCombo->addItem("-- 请选择设备 --", -1);

    Result result = DeviceService::getDeviceList();
    if (result.isSuccess()) {
        QVariantList devices = result.data.toList();
        for (const QVariant &dev : devices) {
            QVariantMap d = dev.toMap();
            m_deviceCombo->addItem(
                QString("%1 - %2").arg(d["modbusAddress"].toInt()).arg(d["name"].toString()),
                d["id"]
            );
        }
    }
}

void MonitorPage::onDeviceChanged(int index)
{
    // Stop current polling if active
    if (m_isPolling) {
        setPollingState(false);
    }

    m_currentDeviceId = m_deviceCombo->itemData(index).toInt();
    m_table->setRowCount(0);

    m_startStopBtn->setEnabled(m_currentDeviceId >= 0);
}

void MonitorPage::onStartStopClicked()
{
    if (m_isPolling) {
        setPollingState(false);
    } else {
        setPollingState(true);
        updateData();  // Initial read
    }
}

void MonitorPage::setPollingState(bool polling)
{
    m_isPolling = polling;

    if (polling) {
        ModbusService::startPolling(m_currentDeviceId);
        m_pollTimer->start(1000);
        m_startStopBtn->setText("停止");
        m_startStopBtn->setStyleSheet(
            "QPushButton { background-color: #ff4444; color: #ffffff; border: none; "
            "border-radius: 6px; padding: 10px 20px; min-height: 40px; font-size: 14pt; font-weight: bold; }"
            "QPushButton:pressed { background-color: #cc3333; }"
        );
        m_statusLed->setStyleSheet("background-color: #00ff88; border-radius: 8px;");
        m_statusLabel->setText("采集中");
        m_statusLabel->setStyleSheet("color: #00ff88; font-size: 11pt;");
    } else {
        ModbusService::stopPolling(m_currentDeviceId);
        m_pollTimer->stop();
        m_startStopBtn->setText("启动");
        m_startStopBtn->setStyleSheet(AppStyle::getButtonStyle(true));
        m_statusLed->setStyleSheet("background-color: #606060; border-radius: 8px;");
        m_statusLabel->setText("已停止");
        m_statusLabel->setStyleSheet("color: #a0a0a0; font-size: 11pt;");
    }
}

void MonitorPage::onPollTimer()
{
    updateData();
}

void MonitorPage::updateData()
{
    if (m_currentDeviceId < 0) return;

    Result result = ModbusService::readHoldingRegisters(m_currentDeviceId);
    if (!result.isSuccess()) {
        m_statusLed->setStyleSheet("background-color: #ff4444; border-radius: 8px;");
        m_statusLabel->setText("错误");
        m_statusLabel->setStyleSheet("color: #ff4444; font-size: 11pt;");
        return;
    }

    m_statusLed->setStyleSheet("background-color: #00ff88; border-radius: 8px;");
    m_statusLabel->setText("正常");
    m_statusLabel->setStyleSheet("color: #00ff88; font-size: 11pt;");

    QVariantList registers = result.data.toList();
    m_table->setRowCount(registers.size());

    for (int i = 0; i < registers.size(); ++i) {
        QVariantMap reg = registers[i].toMap();

        QTableWidgetItem *addrItem = new QTableWidgetItem(QString::number(reg["address"].toInt()));
        addrItem->setTextAlignment(Qt::AlignCenter);
        addrItem->setData(Qt::UserRole, reg["address"]);
        m_table->setItem(i, 0, addrItem);

        QTableWidgetItem *nameItem = new QTableWidgetItem(reg["name"].toString());
        m_table->setItem(i, 1, nameItem);

        QString valueStr = QString("%1 %2").arg(reg["value"].toInt()).arg(reg["unit"].toString());
        QTableWidgetItem *valueItem = new QTableWidgetItem(valueStr);
        valueItem->setTextAlignment(Qt::AlignCenter);
        valueItem->setForeground(QColor("#00ff88"));
        m_table->setItem(i, 2, valueItem);

        QTableWidgetItem *timeItem = new QTableWidgetItem(reg["updateTime"].toString());
        timeItem->setTextAlignment(Qt::AlignCenter);
        timeItem->setForeground(QColor("#a0a0a0"));
        m_table->setItem(i, 3, timeItem);
    }
}

void MonitorPage::onTableDoubleClicked(int row, int column)
{
    Q_UNUSED(column)

    if (m_currentDeviceId < 0) return;

    QTableWidgetItem *item = m_table->item(row, 0);
    if (item) {
        int addr = item->data(Qt::UserRole).toInt();
        emit viewDetail(m_currentDeviceId, addr);
    }
}
