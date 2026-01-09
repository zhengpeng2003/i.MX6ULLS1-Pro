/**
 * @file homepage.cpp
 * @brief 系统首页实现
 *
 * 本文件实现了系统首页的所有功能，包括状态栏、状态卡片、导航按钮的
 * 创建和数据刷新。
 */

#include "homepage.h"
#include "../common/appstyle.h"
#include "../service/systemservice.h"
#include "../service/deviceservice.h"
#include "../service/alarmservice.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDateTime>

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
    , m_statusBar(nullptr)
    , m_timeLabel(nullptr)
    , m_networkIcon(nullptr)
    , m_rs485Icon(nullptr)
    , m_cpuLabel(nullptr)
    , m_memLabel(nullptr)
    , m_deviceCard(nullptr)
    , m_deviceCountLabel(nullptr)
    , m_alarmCard(nullptr)
    , m_alarmCountLabel(nullptr)
    , m_commCard(nullptr)
    , m_commRateLabel(nullptr)
    , m_deviceBtn(nullptr)
    , m_monitorBtn(nullptr)
    , m_alarmBtn(nullptr)
    , m_settingsBtn(nullptr)
    , m_timeTimer(new QTimer(this))
    , m_refreshTimer(new QTimer(this))
{
    setupUI();

    // 设置定时器
    connect(m_timeTimer, &QTimer::timeout, this, &HomePage::updateTime);
    m_timeTimer->start(1000);

    connect(m_refreshTimer, &QTimer::timeout, this, &HomePage::onRefreshTimer);
    m_refreshTimer->start(5000);

    // 初始更新
    updateTime();
    updateStatusCards();
}

HomePage::~HomePage()
{
}

void HomePage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    setupStatusBar();
    mainLayout->addWidget(m_statusBar);

    // Content area
    QWidget *content = new QWidget(this);
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(10, 8, 10, 8);
    contentLayout->setSpacing(8);

    // Status cards section
    QWidget *cardsWidget = new QWidget(this);
    setupStatusCards();
    QHBoxLayout *cardsLayout = new QHBoxLayout(cardsWidget);
    cardsLayout->setContentsMargins(0, 0, 0, 0);
    cardsLayout->setSpacing(8);
    cardsLayout->addWidget(m_deviceCard);
    cardsLayout->addWidget(m_alarmCard);
    cardsLayout->addWidget(m_commCard);
    contentLayout->addWidget(cardsWidget);

    // Navigation buttons section
    QWidget *navWidget = new QWidget(this);
    setupNavigationButtons();
    QGridLayout *navLayout = new QGridLayout(navWidget);
    navLayout->setContentsMargins(0, 0, 0, 0);
    navLayout->setSpacing(8);
    navLayout->addWidget(m_deviceBtn, 0, 0);
    navLayout->addWidget(m_monitorBtn, 0, 1);
    navLayout->addWidget(m_alarmBtn, 1, 0);
    navLayout->addWidget(m_settingsBtn, 1, 1);
    contentLayout->addWidget(navWidget, 1);

    mainLayout->addWidget(content, 1);
}

void HomePage::setupStatusBar()
{
    m_statusBar = new QFrame(this);
    m_statusBar->setFixedHeight(AppStyle::STATUS_BAR_HEIGHT);
    m_statusBar->setStyleSheet(AppStyle::getStatusBarStyle());

    QHBoxLayout *layout = new QHBoxLayout(m_statusBar);
    layout->setContentsMargins(10, 0, 10, 0);
    layout->setSpacing(15);

    // 时间标签
    m_timeLabel = new QLabel(m_statusBar);
    m_timeLabel->setStyleSheet("font-size: 11pt; font-weight: bold;");
    layout->addWidget(m_timeLabel);

    layout->addStretch();

    // 网络状态图标
    m_networkIcon = new QLabel(m_statusBar);
    m_networkIcon->setText("网络");
    m_networkIcon->setStyleSheet("color: #00ff88; font-size: 9pt;");
    layout->addWidget(m_networkIcon);

    // RS485状态图标
    m_rs485Icon = new QLabel(m_statusBar);
    m_rs485Icon->setText("RS485");
    m_rs485Icon->setStyleSheet("color: #00ff88; font-size: 9pt;");
    layout->addWidget(m_rs485Icon);

    // CPU使用率
    m_cpuLabel = new QLabel(m_statusBar);
    m_cpuLabel->setText("CPU: --");
    m_cpuLabel->setStyleSheet("font-size: 9pt;");
    layout->addWidget(m_cpuLabel);

    // 内存使用率
    m_memLabel = new QLabel(m_statusBar);
    m_memLabel->setText("内存: --");
    m_memLabel->setStyleSheet("font-size: 9pt;");
    layout->addWidget(m_memLabel);
}

void HomePage::setupStatusCards()
{
    // 在线设备卡片
    m_deviceCard = new QFrame(this);
    m_deviceCard->setStyleSheet(AppStyle::getCardStyle());
    QVBoxLayout *deviceLayout = new QVBoxLayout(m_deviceCard);
    deviceLayout->setContentsMargins(8, 8, 8, 8);
    deviceLayout->setAlignment(Qt::AlignCenter);

    QLabel *deviceTitle = new QLabel("在线设备", m_deviceCard);
    deviceTitle->setStyleSheet("color: #a0a0a0; font-size: 10pt; background: transparent;");
    deviceTitle->setAlignment(Qt::AlignCenter);
    deviceLayout->addWidget(deviceTitle);

    m_deviceCountLabel = new QLabel("--", m_deviceCard);
    m_deviceCountLabel->setStyleSheet("color: #00ff88; font-size: 20pt; font-weight: bold; background: transparent;");
    m_deviceCountLabel->setAlignment(Qt::AlignCenter);
    deviceLayout->addWidget(m_deviceCountLabel);

    // 告警数量卡片
    m_alarmCard = new QFrame(this);
    m_alarmCard->setStyleSheet(AppStyle::getCardStyle());
    QVBoxLayout *alarmLayout = new QVBoxLayout(m_alarmCard);
    alarmLayout->setContentsMargins(8, 8, 8, 8);
    alarmLayout->setAlignment(Qt::AlignCenter);

    QLabel *alarmTitle = new QLabel("活动告警", m_alarmCard);
    alarmTitle->setStyleSheet("color: #a0a0a0; font-size: 10pt; background: transparent;");
    alarmTitle->setAlignment(Qt::AlignCenter);
    alarmLayout->addWidget(alarmTitle);

    m_alarmCountLabel = new QLabel("--", m_alarmCard);
    m_alarmCountLabel->setStyleSheet("color: #ff4444; font-size: 20pt; font-weight: bold; background: transparent;");
    m_alarmCountLabel->setAlignment(Qt::AlignCenter);
    alarmLayout->addWidget(m_alarmCountLabel);

    // 通信正常率卡片
    m_commCard = new QFrame(this);
    m_commCard->setStyleSheet(AppStyle::getCardStyle());
    QVBoxLayout *commLayout = new QVBoxLayout(m_commCard);
    commLayout->setContentsMargins(8, 8, 8, 8);
    commLayout->setAlignment(Qt::AlignCenter);

    QLabel *commTitle = new QLabel("通信正常率", m_commCard);
    commTitle->setStyleSheet("color: #a0a0a0; font-size: 10pt; background: transparent;");
    commTitle->setAlignment(Qt::AlignCenter);
    commLayout->addWidget(commTitle);

    m_commRateLabel = new QLabel("--%", m_commCard);
    m_commRateLabel->setStyleSheet("color: #ffffff; font-size: 20pt; font-weight: bold; background: transparent;");
    m_commRateLabel->setAlignment(Qt::AlignCenter);
    commLayout->addWidget(m_commRateLabel);
}

void HomePage::setupNavigationButtons()
{
    QString btnStyle =
        "QPushButton {"
        "   background-color: #16213e;"
        "   color: #ffffff;"
        "   border: 2px solid #0f3460;"
        "   border-radius: 10px;"
        "   font-size: 14pt;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #0f3460;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #e94560;"
        "   border-color: #e94560;"
        "}";

    m_deviceBtn = new QPushButton("设备\n管理", this);
    m_deviceBtn->setStyleSheet(btnStyle);
    m_deviceBtn->setMinimumSize(100, 70);
    connect(m_deviceBtn, &QPushButton::clicked, this, &HomePage::navigateToDevices);

    m_monitorBtn = new QPushButton("实时\n监控", this);
    m_monitorBtn->setStyleSheet(btnStyle);
    m_monitorBtn->setMinimumSize(100, 70);
    connect(m_monitorBtn, &QPushButton::clicked, this, &HomePage::navigateToMonitor);

    m_alarmBtn = new QPushButton("告警\n中心", this);
    m_alarmBtn->setStyleSheet(btnStyle);
    m_alarmBtn->setMinimumSize(100, 70);
    connect(m_alarmBtn, &QPushButton::clicked, this, &HomePage::navigateToAlarms);

    m_settingsBtn = new QPushButton("系统\n设置", this);
    m_settingsBtn->setStyleSheet(btnStyle);
    m_settingsBtn->setMinimumSize(100, 70);
    connect(m_settingsBtn, &QPushButton::clicked, this, &HomePage::navigateToSettings);
}

void HomePage::updateTime()
{
    QDateTime now = QDateTime::currentDateTime();
    m_timeLabel->setText(now.toString("yyyy-MM-dd hh:mm:ss"));
}

void HomePage::onRefreshTimer()
{
    updateStatusCards();
}

void HomePage::refreshStatus()
{
    updateStatusCards();
}

void HomePage::updateStatusCards()
{
    // 获取系统信息
    Result sysResult = SystemService::getSystemInfo();
    if (sysResult.isSuccess()) {
        QVariantMap info = sysResult.data.toMap();
        m_cpuLabel->setText(QString("CPU: %1%").arg(info["cpu"].toInt()));
        m_memLabel->setText(QString("内存: %1%").arg(info["mem"].toInt()));
    }

    // 获取通信状态
    Result commResult = SystemService::getCommStatus();
    if (commResult.isSuccess()) {
        QVariantMap status = commResult.data.toMap();

        // 更新网络状态
        bool netOk = status["network"].toBool();
        m_networkIcon->setStyleSheet(netOk ? "color: #00ff88; font-size: 9pt;" : "color: #ff4444; font-size: 9pt;");

        // 更新RS485状态
        bool rs485Ok = status["rs485"].toBool();
        m_rs485Icon->setStyleSheet(rs485Ok ? "color: #00ff88; font-size: 9pt;" : "color: #ff4444; font-size: 9pt;");

        // 更新通信正常率
        int commRate = status["commRate"].toInt();
        m_commRateLabel->setText(QString("%1%").arg(commRate));
        if (commRate >= 90) {
            m_commRateLabel->setStyleSheet("color: #00ff88; font-size: 20pt; font-weight: bold; background: transparent;");
        } else if (commRate >= 70) {
            m_commRateLabel->setStyleSheet("color: #ffaa00; font-size: 20pt; font-weight: bold; background: transparent;");
        } else {
            m_commRateLabel->setStyleSheet("color: #ff4444; font-size: 20pt; font-weight: bold; background: transparent;");
        }
    }

    // 获取设备数量
    Result deviceResult = DeviceService::getDeviceList();
    if (deviceResult.isSuccess()) {
        QVariantList devices = deviceResult.data.toList();
        int onlineCount = 0;
        for (const QVariant &dev : devices) {
            if (dev.toMap()["online"].toBool()) {
                onlineCount++;
            }
        }
        m_deviceCountLabel->setText(QString::number(onlineCount));
    }

    // 获取告警数量
    Result alarmResult = AlarmService::getAlarmList();
    if (alarmResult.isSuccess()) {
        QVariantList alarms = alarmResult.data.toList();
        int activeCount = 0;
        for (const QVariant &alarm : alarms) {
            if (!alarm.toMap()["acknowledged"].toBool()) {
                activeCount++;
            }
        }
        m_alarmCountLabel->setText(QString::number(activeCount));
        if (activeCount > 0) {
            m_alarmCountLabel->setStyleSheet("color: #ff4444; font-size: 20pt; font-weight: bold; background: transparent;");
        } else {
            m_alarmCountLabel->setStyleSheet("color: #00ff88; font-size: 20pt; font-weight: bold; background: transparent;");
        }
    }
}
