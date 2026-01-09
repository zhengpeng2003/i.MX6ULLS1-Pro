/**
 * @file mainwindow.cpp
 * @brief 主窗口实现
 *
 * 本文件实现了主窗口的所有功能，包括界面初始化、页面创建、
 * 信号连接和页面导航逻辑。
 */

#include "mainwindow.h"
#include "common/appstyle.h"

// 包含所有页面头文件
#include "home/homepage.h"
#include "device/devicelistpage.h"
#include "device/deviceconfigpage.h"
#include "monitor/monitorpage.h"
#include "monitor/datadetailpage.h"
#include "alarm/alarmcenterpage.h"
#include "alarm/alarmrulepage.h"
#include "settings/settingspage.h"
#include "settings/networkpage.h"
#include "settings/mqttconfigpage.h"
#include "settings/logpage.h"
#include "help/helppage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_stackWidget(nullptr)
    , m_homePage(nullptr)
    , m_deviceListPage(nullptr)
    , m_deviceConfigPage(nullptr)
    , m_monitorPage(nullptr)
    , m_dataDetailPage(nullptr)
    , m_alarmCenterPage(nullptr)
    , m_alarmRulePage(nullptr)
    , m_settingsPage(nullptr)
    , m_networkPage(nullptr)
    , m_mqttConfigPage(nullptr)
    , m_logPage(nullptr)
    , m_helpPage(nullptr)
{
    setupUI();
    createPages();
    connectSignals();

    // 启动时显示首页
    navigateTo(PAGE_HOME);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // 设置固定尺寸以适配480x272屏幕
    setFixedSize(AppStyle::SCREEN_WIDTH, AppStyle::SCREEN_HEIGHT);

    // 移除窗口边框以适配嵌入式显示
    setWindowFlags(Qt::FramelessWindowHint);

    // 设置窗口标题
    setWindowTitle("工业监控系统");

    // 创建页面堆栈容器
    m_stackWidget = new QStackedWidget(this);
    setCentralWidget(m_stackWidget);
}

void MainWindow::createPages()
{
    // 创建所有页面并添加到堆栈
    m_homePage = new HomePage(this);
    m_stackWidget->addWidget(m_homePage);  // 索引 0

    m_deviceListPage = new DeviceListPage(this);
    m_stackWidget->addWidget(m_deviceListPage);  // 索引 1

    m_deviceConfigPage = new DeviceConfigPage(this);
    m_stackWidget->addWidget(m_deviceConfigPage);  // 索引 2

    m_monitorPage = new MonitorPage(this);
    m_stackWidget->addWidget(m_monitorPage);  // 索引 3

    m_dataDetailPage = new DataDetailPage(this);
    m_stackWidget->addWidget(m_dataDetailPage);  // 索引 4

    m_alarmCenterPage = new AlarmCenterPage(this);
    m_stackWidget->addWidget(m_alarmCenterPage);  // 索引 5

    m_alarmRulePage = new AlarmRulePage(this);
    m_stackWidget->addWidget(m_alarmRulePage);  // 索引 6

    m_settingsPage = new SettingsPage(this);
    m_stackWidget->addWidget(m_settingsPage);  // 索引 7

    m_networkPage = new NetworkPage(this);
    m_stackWidget->addWidget(m_networkPage);  // 索引 8

    m_mqttConfigPage = new MqttConfigPage(this);
    m_stackWidget->addWidget(m_mqttConfigPage);  // 索引 9

    m_logPage = new LogPage(this);
    m_stackWidget->addWidget(m_logPage);  // 索引 10

    m_helpPage = new HelpPage(this);
    m_stackWidget->addWidget(m_helpPage);  // 索引 11
}

void MainWindow::connectSignals()
{
    // 首页导航信号
    connect(m_homePage, &HomePage::navigateToDevices, this, [this]() {
        navigateTo(PAGE_DEVICE_LIST);
    });
    connect(m_homePage, &HomePage::navigateToMonitor, this, [this]() {
        navigateTo(PAGE_MONITOR);
    });
    connect(m_homePage, &HomePage::navigateToAlarms, this, [this]() {
        navigateTo(PAGE_ALARM_CENTER);
    });
    connect(m_homePage, &HomePage::navigateToSettings, this, [this]() {
        navigateTo(PAGE_SETTINGS);
    });

    // 设备列表页信号
    connect(m_deviceListPage, &DeviceListPage::goBack, this, &MainWindow::goBack);
    connect(m_deviceListPage, &DeviceListPage::editDevice, this, [this](int deviceId) {
        navigateTo(PAGE_DEVICE_CONFIG, deviceId);
    });
    connect(m_deviceListPage, &DeviceListPage::addDevice, this, [this]() {
        navigateTo(PAGE_DEVICE_CONFIG, -1);  // -1 表示新增设备
    });

    // 设备配置页信号
    connect(m_deviceConfigPage, &DeviceConfigPage::goBack, this, &MainWindow::goBack);
    connect(m_deviceConfigPage, &DeviceConfigPage::saved, this, &MainWindow::goBack);

    // 监控页信号
    connect(m_monitorPage, &MonitorPage::goBack, this, &MainWindow::goBack);
    connect(m_monitorPage, &MonitorPage::viewDetail, this, [this](int deviceId, int addr) {
        QVariantMap param;
        param["deviceId"] = deviceId;
        param["addr"] = addr;
        navigateTo(PAGE_DATA_DETAIL, param);
    });

    // 数据详情页信号
    connect(m_dataDetailPage, &DataDetailPage::goBack, this, &MainWindow::goBack);

    // 告警中心页信号
    connect(m_alarmCenterPage, &AlarmCenterPage::goBack, this, &MainWindow::goBack);
    connect(m_alarmCenterPage, &AlarmCenterPage::configureRules, this, [this]() {
        navigateTo(PAGE_ALARM_RULE);
    });

    // 告警规则页信号
    connect(m_alarmRulePage, &AlarmRulePage::goBack, this, &MainWindow::goBack);

    // 设置页信号
    connect(m_settingsPage, &SettingsPage::goBack, this, &MainWindow::goBack);
    connect(m_settingsPage, &SettingsPage::navigateToNetwork, this, [this]() {
        navigateTo(PAGE_NETWORK);
    });
    connect(m_settingsPage, &SettingsPage::navigateToMqtt, this, [this]() {
        navigateTo(PAGE_MQTT_CONFIG);
    });
    connect(m_settingsPage, &SettingsPage::navigateToLog, this, [this]() {
        navigateTo(PAGE_LOG);
    });
    connect(m_settingsPage, &SettingsPage::navigateToHelp, this, [this]() {
        navigateTo(PAGE_HELP);
    });

    // 网络设置页信号
    connect(m_networkPage, &NetworkPage::goBack, this, &MainWindow::goBack);

    // MQTT配置页信号
    connect(m_mqttConfigPage, &MqttConfigPage::goBack, this, &MainWindow::goBack);

    // 日志页信号
    connect(m_logPage, &LogPage::goBack, this, &MainWindow::goBack);

    // 帮助页信号
    connect(m_helpPage, &HelpPage::goBack, this, &MainWindow::goBack);
}

void MainWindow::navigateTo(PageIndex page)
{
    navigateTo(page, QVariant());
}

void MainWindow::navigateTo(PageIndex page, const QVariant &param)
{
    if (page < 0 || page >= PAGE_COUNT) {
        return;
    }

    // 保存当前页面到历史记录
    PageIndex current = currentPage();
    if (current != page) {
        m_pageHistory.push(current);
    }

    // 切换页面
    m_stackWidget->setCurrentIndex(page);

    // 根据页面类型传递参数
    switch (page) {
    case PAGE_DEVICE_CONFIG:
        m_deviceConfigPage->loadDevice(param.toInt());
        break;
    case PAGE_DATA_DETAIL:
        if (param.type() == QVariant::Map) {
            QVariantMap map = param.toMap();
            m_dataDetailPage->loadData(map["deviceId"].toInt(), map["addr"].toInt());
        }
        break;
    default:
        break;
    }

    emit pageChanged(page);
}

void MainWindow::goBack()
{
    if (m_pageHistory.isEmpty()) {
        navigateTo(PAGE_HOME);
        return;
    }

    PageIndex prevPage = m_pageHistory.pop();
    m_stackWidget->setCurrentIndex(prevPage);
    emit pageChanged(prevPage);
}

PageIndex MainWindow::currentPage() const
{
    return static_cast<PageIndex>(m_stackWidget->currentIndex());
}
