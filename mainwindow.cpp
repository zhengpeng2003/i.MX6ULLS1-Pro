#include "mainwindow.h"
#include "common/appstyle.h"

// Include all page headers
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

    // Start at home page
    navigateTo(PAGE_HOME);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Set fixed size for 480x272 screen
    setFixedSize(AppStyle::SCREEN_WIDTH, AppStyle::SCREEN_HEIGHT);

    // Remove window frame for embedded display
    setWindowFlags(Qt::FramelessWindowHint);

    // Set window title
    setWindowTitle("Industrial Monitor System");

    // Create stacked widget
    m_stackWidget = new QStackedWidget(this);
    setCentralWidget(m_stackWidget);
}

void MainWindow::createPages()
{
    // Create all pages and add to stack
    m_homePage = new HomePage(this);
    m_stackWidget->addWidget(m_homePage);  // index 0

    m_deviceListPage = new DeviceListPage(this);
    m_stackWidget->addWidget(m_deviceListPage);  // index 1

    m_deviceConfigPage = new DeviceConfigPage(this);
    m_stackWidget->addWidget(m_deviceConfigPage);  // index 2

    m_monitorPage = new MonitorPage(this);
    m_stackWidget->addWidget(m_monitorPage);  // index 3

    m_dataDetailPage = new DataDetailPage(this);
    m_stackWidget->addWidget(m_dataDetailPage);  // index 4

    m_alarmCenterPage = new AlarmCenterPage(this);
    m_stackWidget->addWidget(m_alarmCenterPage);  // index 5

    m_alarmRulePage = new AlarmRulePage(this);
    m_stackWidget->addWidget(m_alarmRulePage);  // index 6

    m_settingsPage = new SettingsPage(this);
    m_stackWidget->addWidget(m_settingsPage);  // index 7

    m_networkPage = new NetworkPage(this);
    m_stackWidget->addWidget(m_networkPage);  // index 8

    m_mqttConfigPage = new MqttConfigPage(this);
    m_stackWidget->addWidget(m_mqttConfigPage);  // index 9

    m_logPage = new LogPage(this);
    m_stackWidget->addWidget(m_logPage);  // index 10

    m_helpPage = new HelpPage(this);
    m_stackWidget->addWidget(m_helpPage);  // index 11
}

void MainWindow::connectSignals()
{
    // Home page navigation
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

    // Device list page
    connect(m_deviceListPage, &DeviceListPage::goBack, this, &MainWindow::goBack);
    connect(m_deviceListPage, &DeviceListPage::editDevice, this, [this](int deviceId) {
        navigateTo(PAGE_DEVICE_CONFIG, deviceId);
    });
    connect(m_deviceListPage, &DeviceListPage::addDevice, this, [this]() {
        navigateTo(PAGE_DEVICE_CONFIG, -1);  // -1 means new device
    });

    // Device config page
    connect(m_deviceConfigPage, &DeviceConfigPage::goBack, this, &MainWindow::goBack);
    connect(m_deviceConfigPage, &DeviceConfigPage::saved, this, &MainWindow::goBack);

    // Monitor page
    connect(m_monitorPage, &MonitorPage::goBack, this, &MainWindow::goBack);
    connect(m_monitorPage, &MonitorPage::viewDetail, this, [this](int deviceId, int addr) {
        QVariantMap param;
        param["deviceId"] = deviceId;
        param["addr"] = addr;
        navigateTo(PAGE_DATA_DETAIL, param);
    });

    // Data detail page
    connect(m_dataDetailPage, &DataDetailPage::goBack, this, &MainWindow::goBack);

    // Alarm center page
    connect(m_alarmCenterPage, &AlarmCenterPage::goBack, this, &MainWindow::goBack);
    connect(m_alarmCenterPage, &AlarmCenterPage::configureRules, this, [this]() {
        navigateTo(PAGE_ALARM_RULE);
    });

    // Alarm rule page
    connect(m_alarmRulePage, &AlarmRulePage::goBack, this, &MainWindow::goBack);

    // Settings page
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

    // Network page
    connect(m_networkPage, &NetworkPage::goBack, this, &MainWindow::goBack);

    // MQTT config page
    connect(m_mqttConfigPage, &MqttConfigPage::goBack, this, &MainWindow::goBack);

    // Log page
    connect(m_logPage, &LogPage::goBack, this, &MainWindow::goBack);

    // Help page
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

    // Save current page to history
    PageIndex current = currentPage();
    if (current != page) {
        m_pageHistory.push(current);
    }

    // Switch page
    m_stackWidget->setCurrentIndex(page);

    // Notify page of parameter if applicable
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
