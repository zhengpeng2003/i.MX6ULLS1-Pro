#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QStack>

// Page index enumeration
enum PageIndex {
    PAGE_HOME = 0,
    PAGE_DEVICE_LIST,
    PAGE_DEVICE_CONFIG,
    PAGE_MONITOR,
    PAGE_DATA_DETAIL,
    PAGE_ALARM_CENTER,
    PAGE_ALARM_RULE,
    PAGE_SETTINGS,
    PAGE_NETWORK,
    PAGE_MQTT_CONFIG,
    PAGE_LOG,
    PAGE_HELP,
    PAGE_COUNT
};

// Forward declarations
class HomePage;
class DeviceListPage;
class DeviceConfigPage;
class MonitorPage;
class DataDetailPage;
class AlarmCenterPage;
class AlarmRulePage;
class SettingsPage;
class NetworkPage;
class MqttConfigPage;
class LogPage;
class HelpPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Navigation methods
    void navigateTo(PageIndex page);
    void navigateTo(PageIndex page, const QVariant &param);
    void goBack();
    PageIndex currentPage() const;

    // Get page instances for signal connections
    HomePage* homePage() const { return m_homePage; }
    DeviceListPage* deviceListPage() const { return m_deviceListPage; }
    DeviceConfigPage* deviceConfigPage() const { return m_deviceConfigPage; }
    MonitorPage* monitorPage() const { return m_monitorPage; }
    DataDetailPage* dataDetailPage() const { return m_dataDetailPage; }
    AlarmCenterPage* alarmCenterPage() const { return m_alarmCenterPage; }
    AlarmRulePage* alarmRulePage() const { return m_alarmRulePage; }
    SettingsPage* settingsPage() const { return m_settingsPage; }
    NetworkPage* networkPage() const { return m_networkPage; }
    MqttConfigPage* mqttConfigPage() const { return m_mqttConfigPage; }
    LogPage* logPage() const { return m_logPage; }
    HelpPage* helpPage() const { return m_helpPage; }

signals:
    void pageChanged(PageIndex page);

private:
    void setupUI();
    void createPages();
    void connectSignals();

    QStackedWidget *m_stackWidget;
    QStack<PageIndex> m_pageHistory;

    // Page instances
    HomePage *m_homePage;
    DeviceListPage *m_deviceListPage;
    DeviceConfigPage *m_deviceConfigPage;
    MonitorPage *m_monitorPage;
    DataDetailPage *m_dataDetailPage;
    AlarmCenterPage *m_alarmCenterPage;
    AlarmRulePage *m_alarmRulePage;
    SettingsPage *m_settingsPage;
    NetworkPage *m_networkPage;
    MqttConfigPage *m_mqttConfigPage;
    LogPage *m_logPage;
    HelpPage *m_helpPage;
};

#endif // MAINWINDOW_H
