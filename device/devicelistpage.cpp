/**
 * @file devicelistpage.cpp
 * @brief 设备列表页面实现
 *
 * 本文件实现了设备列表页面的所有功能，包括表格显示、
 * 设备增删改查、扫描设备等操作。
 */

#include "devicelistpage.h"
#include "../common/appstyle.h"
#include "../common/toast.h"
#include "../common/confirmdialog.h"
#include "../service/deviceservice.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTimer>

DeviceListPage::DeviceListPage(QWidget *parent)
    : QWidget(parent)
    , m_titleBar(nullptr)
    , m_backBtn(nullptr)
    , m_titleLabel(nullptr)
    , m_table(nullptr)
    , m_scanProgress(nullptr)
    , m_buttonBar(nullptr)
    , m_addBtn(nullptr)
    , m_editBtn(nullptr)
    , m_deleteBtn(nullptr)
    , m_scanBtn(nullptr)
{
    setupUI();
    loadDevices();
}

DeviceListPage::~DeviceListPage()
{
}

void DeviceListPage::setupUI()
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

    setupTable();
    contentLayout->addWidget(m_table, 1);

    // Progress bar (hidden by default)
    m_scanProgress = new QProgressBar(this);
    m_scanProgress->setFixedHeight(20);
    m_scanProgress->setRange(0, 100);
    m_scanProgress->setValue(0);
    m_scanProgress->setVisible(false);
    contentLayout->addWidget(m_scanProgress);

    setupButtons();
    contentLayout->addWidget(m_buttonBar);

    mainLayout->addWidget(content, 1);
}

void DeviceListPage::setupTitleBar()
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
    connect(m_backBtn, &QPushButton::clicked, this, &DeviceListPage::goBack);
    layout->addWidget(m_backBtn);

    m_titleLabel = new QLabel("设备管理", m_titleBar);
    m_titleLabel->setStyleSheet("color: #ffffff; font-size: 16pt; font-weight: bold;");
    layout->addWidget(m_titleLabel);

    layout->addStretch();
}

void DeviceListPage::setupTable()
{
    m_table = new QTableWidget(this);
    m_table->setColumnCount(4);
    m_table->setHorizontalHeaderLabels(QStringList() << "地址" << "名称" << "类型" << "状态");
    m_table->setStyleSheet(AppStyle::getTableStyle());
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->verticalHeader()->setVisible(false);
    m_table->setShowGrid(false);

    // 设置列宽
    m_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    m_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    m_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    m_table->setColumnWidth(0, 50);
    m_table->setColumnWidth(2, 80);
    m_table->setColumnWidth(3, 70);

    // 行高适配触控
    m_table->verticalHeader()->setDefaultSectionSize(36);

    connect(m_table, &QTableWidget::itemSelectionChanged,
            this, &DeviceListPage::onTableSelectionChanged);
    connect(m_table, &QTableWidget::cellDoubleClicked, this, [this](int row, int) {
        QTableWidgetItem *item = m_table->item(row, 0);
        if (item) {
            int deviceId = item->data(Qt::UserRole).toInt();
            emit editDevice(deviceId);
        }
    });
}

void DeviceListPage::setupButtons()
{
    m_buttonBar = new QWidget(this);
    m_buttonBar->setFixedHeight(50);

    QHBoxLayout *layout = new QHBoxLayout(m_buttonBar);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);

    QString btnStyle = AppStyle::getButtonStyle(false);
    QString primaryStyle = AppStyle::getButtonStyle(true);

    m_addBtn = new QPushButton("添加", m_buttonBar);
    m_addBtn->setStyleSheet(primaryStyle);
    m_addBtn->setMinimumHeight(44);
    connect(m_addBtn, &QPushButton::clicked, this, &DeviceListPage::onAddClicked);
    layout->addWidget(m_addBtn);

    m_editBtn = new QPushButton("编辑", m_buttonBar);
    m_editBtn->setStyleSheet(btnStyle);
    m_editBtn->setMinimumHeight(44);
    m_editBtn->setEnabled(false);
    connect(m_editBtn, &QPushButton::clicked, this, &DeviceListPage::onEditClicked);
    layout->addWidget(m_editBtn);

    m_deleteBtn = new QPushButton("删除", m_buttonBar);
    m_deleteBtn->setStyleSheet(btnStyle);
    m_deleteBtn->setMinimumHeight(44);
    m_deleteBtn->setEnabled(false);
    connect(m_deleteBtn, &QPushButton::clicked, this, &DeviceListPage::onDeleteClicked);
    layout->addWidget(m_deleteBtn);

    m_scanBtn = new QPushButton("扫描", m_buttonBar);
    m_scanBtn->setStyleSheet(btnStyle);
    m_scanBtn->setMinimumHeight(44);
    connect(m_scanBtn, &QPushButton::clicked, this, &DeviceListPage::onScanClicked);
    layout->addWidget(m_scanBtn);
}

void DeviceListPage::loadDevices()
{
    Result result = DeviceService::getDeviceList();
    if (!result.isSuccess()) {
        Toast::showError(this, result.message);
        return;
    }

    QVariantList devices = result.data.toList();
    m_table->setRowCount(devices.size());

    for (int i = 0; i < devices.size(); ++i) {
        QVariantMap dev = devices[i].toMap();

        QTableWidgetItem *addrItem = new QTableWidgetItem(QString::number(dev["modbusAddress"].toInt()));
        addrItem->setData(Qt::UserRole, dev["id"]);
        addrItem->setTextAlignment(Qt::AlignCenter);
        m_table->setItem(i, 0, addrItem);

        QTableWidgetItem *nameItem = new QTableWidgetItem(dev["name"].toString());
        m_table->setItem(i, 1, nameItem);

        QTableWidgetItem *typeItem = new QTableWidgetItem(dev["type"].toString());
        typeItem->setTextAlignment(Qt::AlignCenter);
        m_table->setItem(i, 2, typeItem);

        QTableWidgetItem *statusItem = new QTableWidgetItem(dev["status"].toString());
        statusItem->setTextAlignment(Qt::AlignCenter);
        if (dev["online"].toBool()) {
            statusItem->setForeground(QColor("#00ff88"));
        } else {
            statusItem->setForeground(QColor("#ff4444"));
        }
        m_table->setItem(i, 3, statusItem);
    }
}

void DeviceListPage::refreshList()
{
    loadDevices();
}

int DeviceListPage::getSelectedDeviceId() const
{
    QList<QTableWidgetItem*> items = m_table->selectedItems();
    if (items.isEmpty()) {
        return -1;
    }
    int row = items.first()->row();
    QTableWidgetItem *idItem = m_table->item(row, 0);
    return idItem ? idItem->data(Qt::UserRole).toInt() : -1;
}

void DeviceListPage::onTableSelectionChanged()
{
    bool hasSelection = !m_table->selectedItems().isEmpty();
    m_editBtn->setEnabled(hasSelection);
    m_deleteBtn->setEnabled(hasSelection);
}

void DeviceListPage::onAddClicked()
{
    emit addDevice();
}

void DeviceListPage::onEditClicked()
{
    int deviceId = getSelectedDeviceId();
    if (deviceId >= 0) {
        emit editDevice(deviceId);
    }
}

void DeviceListPage::onDeleteClicked()
{
    int deviceId = getSelectedDeviceId();
    if (deviceId < 0) return;

    if (ConfirmDialog::confirm(this, "确认删除", "确定要删除此设备吗？")) {
        Result result = DeviceService::removeDevice(deviceId);
        if (result.isSuccess()) {
            Toast::showSuccess(this, "设备已删除");
            loadDevices();
        } else {
            Toast::showError(this, result.message);
        }
    }
}

void DeviceListPage::onScanClicked()
{
    m_scanBtn->setEnabled(false);
    m_scanProgress->setVisible(true);
    m_scanProgress->setValue(0);

    // 模拟扫描进度
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, timer]() {
        int value = m_scanProgress->value() + 10;
        m_scanProgress->setValue(value);

        if (value >= 100) {
            timer->stop();
            timer->deleteLater();
            m_scanProgress->setVisible(false);
            m_scanBtn->setEnabled(true);

            Result result = DeviceService::scanModbusDevices();
            if (result.isSuccess()) {
                QVariantList found = result.data.toList();
                Toast::showSuccess(this, QString("发现 %1 个设备").arg(found.size()));
            }
        }
    });
    timer->start(200);
}
