/**
 * @file datadetailpage.cpp
 * @brief 数据详情页面实现
 *
 * 本文件实现了数据详情页面的所有功能，包括当前值显示、
 * 统计信息显示、趋势图占位等。
 */

#include "datadetailpage.h"
#include "../common/appstyle.h"
#include "../service/modbusservice.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

DataDetailPage::DataDetailPage(QWidget *parent)
    : QWidget(parent)
    , m_deviceId(-1)
    , m_registerAddr(-1)
    , m_titleBar(nullptr)
    , m_backBtn(nullptr)
    , m_titleLabel(nullptr)
    , m_valueCard(nullptr)
    , m_currentValueLabel(nullptr)
    , m_unitLabel(nullptr)
    , m_updateTimeLabel(nullptr)
    , m_statsCard(nullptr)
    , m_minValueLabel(nullptr)
    , m_maxValueLabel(nullptr)
    , m_avgValueLabel(nullptr)
    , m_chartPlaceholder(nullptr)
    , m_chartLabel(nullptr)
    , m_refreshTimer(new QTimer(this))
{
    setupUI();

    connect(m_refreshTimer, &QTimer::timeout, this, &DataDetailPage::onRefreshTimer);
}

DataDetailPage::~DataDetailPage()
{
}

void DataDetailPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    setupTitleBar();
    mainLayout->addWidget(m_titleBar);

    setupContent();
}

void DataDetailPage::setupTitleBar()
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
    connect(m_backBtn, &QPushButton::clicked, this, &DataDetailPage::goBack);
    layout->addWidget(m_backBtn);

    m_titleLabel = new QLabel("数据详情", m_titleBar);
    m_titleLabel->setStyleSheet("color: #ffffff; font-size: 16pt; font-weight: bold;");
    layout->addWidget(m_titleLabel);

    layout->addStretch();
}

void DataDetailPage::setupContent()
{
    QWidget *content = new QWidget(this);
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(10, 8, 10, 8);
    contentLayout->setSpacing(8);

    // 当前值卡片
    m_valueCard = new QFrame(content);
    m_valueCard->setStyleSheet(AppStyle::getCardStyle());
    QVBoxLayout *valueLayout = new QVBoxLayout(m_valueCard);
    valueLayout->setAlignment(Qt::AlignCenter);

    QLabel *valueTitle = new QLabel("当前值", m_valueCard);
    valueTitle->setStyleSheet("color: #a0a0a0; font-size: 10pt; background: transparent;");
    valueTitle->setAlignment(Qt::AlignCenter);
    valueLayout->addWidget(valueTitle);

    QHBoxLayout *valueRow = new QHBoxLayout();
    valueRow->setAlignment(Qt::AlignCenter);

    m_currentValueLabel = new QLabel("--", m_valueCard);
    m_currentValueLabel->setStyleSheet("color: #00ff88; font-size: 36pt; font-weight: bold; background: transparent;");
    valueRow->addWidget(m_currentValueLabel);

    m_unitLabel = new QLabel("", m_valueCard);
    m_unitLabel->setStyleSheet("color: #a0a0a0; font-size: 14pt; background: transparent;");
    valueRow->addWidget(m_unitLabel);

    valueLayout->addLayout(valueRow);

    m_updateTimeLabel = new QLabel("最后更新: --", m_valueCard);
    m_updateTimeLabel->setStyleSheet("color: #606060; font-size: 9pt; background: transparent;");
    m_updateTimeLabel->setAlignment(Qt::AlignCenter);
    valueLayout->addWidget(m_updateTimeLabel);

    contentLayout->addWidget(m_valueCard);

    // 统计卡片
    m_statsCard = new QFrame(content);
    m_statsCard->setStyleSheet(AppStyle::getCardStyle());
    QHBoxLayout *statsLayout = new QHBoxLayout(m_statsCard);
    statsLayout->setSpacing(20);

    // 最小值
    QVBoxLayout *minLayout = new QVBoxLayout();
    minLayout->setAlignment(Qt::AlignCenter);
    QLabel *minTitle = new QLabel("最小值", m_statsCard);
    minTitle->setStyleSheet("color: #a0a0a0; font-size: 10pt; background: transparent;");
    minTitle->setAlignment(Qt::AlignCenter);
    minLayout->addWidget(minTitle);
    m_minValueLabel = new QLabel("--", m_statsCard);
    m_minValueLabel->setStyleSheet("color: #00aaff; font-size: 16pt; font-weight: bold; background: transparent;");
    m_minValueLabel->setAlignment(Qt::AlignCenter);
    minLayout->addWidget(m_minValueLabel);
    statsLayout->addLayout(minLayout);

    // 最大值
    QVBoxLayout *maxLayout = new QVBoxLayout();
    maxLayout->setAlignment(Qt::AlignCenter);
    QLabel *maxTitle = new QLabel("最大值", m_statsCard);
    maxTitle->setStyleSheet("color: #a0a0a0; font-size: 10pt; background: transparent;");
    maxTitle->setAlignment(Qt::AlignCenter);
    maxLayout->addWidget(maxTitle);
    m_maxValueLabel = new QLabel("--", m_statsCard);
    m_maxValueLabel->setStyleSheet("color: #ff6666; font-size: 16pt; font-weight: bold; background: transparent;");
    m_maxValueLabel->setAlignment(Qt::AlignCenter);
    maxLayout->addWidget(m_maxValueLabel);
    statsLayout->addLayout(maxLayout);

    // 平均值
    QVBoxLayout *avgLayout = new QVBoxLayout();
    avgLayout->setAlignment(Qt::AlignCenter);
    QLabel *avgTitle = new QLabel("平均值", m_statsCard);
    avgTitle->setStyleSheet("color: #a0a0a0; font-size: 10pt; background: transparent;");
    avgTitle->setAlignment(Qt::AlignCenter);
    avgLayout->addWidget(avgTitle);
    m_avgValueLabel = new QLabel("--", m_statsCard);
    m_avgValueLabel->setStyleSheet("color: #ffaa00; font-size: 16pt; font-weight: bold; background: transparent;");
    m_avgValueLabel->setAlignment(Qt::AlignCenter);
    avgLayout->addWidget(m_avgValueLabel);
    statsLayout->addLayout(avgLayout);

    contentLayout->addWidget(m_statsCard);

    // 趋势图占位
    m_chartPlaceholder = new QFrame(content);
    m_chartPlaceholder->setStyleSheet(
        "QFrame { background-color: #16213e; border: 2px dashed #0f3460; border-radius: 8px; }"
    );
    QVBoxLayout *chartLayout = new QVBoxLayout(m_chartPlaceholder);
    chartLayout->setAlignment(Qt::AlignCenter);

    m_chartLabel = new QLabel("趋势图\n（QChart占位）", m_chartPlaceholder);
    m_chartLabel->setStyleSheet("color: #606060; font-size: 12pt; background: transparent;");
    m_chartLabel->setAlignment(Qt::AlignCenter);
    chartLayout->addWidget(m_chartLabel);

    contentLayout->addWidget(m_chartPlaceholder, 1);

    static_cast<QVBoxLayout*>(layout())->addWidget(content, 1);
}

void DataDetailPage::loadData(int deviceId, int addr)
{
    m_deviceId = deviceId;
    m_registerAddr = addr;

    m_titleLabel->setText(QString("寄存器 %1").arg(addr));

    updateData();
    m_refreshTimer->start(2000);
}

void DataDetailPage::onRefreshTimer()
{
    updateData();
}

void DataDetailPage::updateData()
{
    if (m_deviceId < 0 || m_registerAddr < 0) return;

    Result result = ModbusService::getHistoryData(m_deviceId, m_registerAddr);
    if (!result.isSuccess()) {
        return;
    }

    QVariantMap data = result.data.toMap();

    m_currentValueLabel->setText(QString::number(data["currentValue"].toDouble(), 'f', 1));
    m_unitLabel->setText("℃");
    m_updateTimeLabel->setText(QString("最后更新: %1").arg(data["updateTime"].toString()));

    m_minValueLabel->setText(QString::number(data["minValue"].toDouble(), 'f', 1));
    m_maxValueLabel->setText(QString::number(data["maxValue"].toDouble(), 'f', 1));
    m_avgValueLabel->setText(QString::number(data["avgValue"].toDouble(), 'f', 1));
}
