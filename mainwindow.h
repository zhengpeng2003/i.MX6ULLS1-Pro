/**
 * @file mainwindow.h
 * @brief 主窗口定义
 *
 * 本文件定义了应用程序的主窗口类，负责管理所有页面的切换和导航。
 * 使用QStackedWidget实现页面堆栈管理，支持页面历史记录和返回功能。
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QStack>

/**
 * @enum PageIndex
 * @brief 页面索引枚举
 *
 * 定义系统中所有页面的索引值，用于页面导航。
 */
enum PageIndex {
    PAGE_HOME = 0,          ///< 首页
    PAGE_DEVICE_LIST,       ///< 设备列表页
    PAGE_DEVICE_CONFIG,     ///< 设备配置页
    PAGE_MONITOR,           ///< 实时监控页
    PAGE_DATA_DETAIL,       ///< 数据详情页
    PAGE_ALARM_CENTER,      ///< 告警中心页
    PAGE_ALARM_RULE,        ///< 告警规则页
    PAGE_SETTINGS,          ///< 系统设置页
    PAGE_NETWORK,           ///< 网络设置页
    PAGE_MQTT_CONFIG,       ///< MQTT配置页
    PAGE_LOG,               ///< 日志查看页
    PAGE_HELP,              ///< 帮助页
    PAGE_COUNT              ///< 页面总数
};

// 前向声明
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

/**
 * @class MainWindow
 * @brief 主窗口类
 *
 * 应用程序的主窗口，管理所有页面的生命周期和导航逻辑。
 * 提供页面切换、历史记录管理和信号连接等功能。
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~MainWindow();

    /**
     * @brief 导航到指定页面
     * @param page 目标页面索引
     */
    void navigateTo(PageIndex page);

    /**
     * @brief 导航到指定页面并传递参数
     * @param page 目标页面索引
     * @param param 传递给目标页面的参数
     */
    void navigateTo(PageIndex page, const QVariant &param);

    /**
     * @brief 返回上一页
     */
    void goBack();

    /**
     * @brief 获取当前页面索引
     * @return 当前页面的索引值
     */
    PageIndex currentPage() const;

    // 获取各页面实例（用于信号连接）
    HomePage* homePage() const { return m_homePage; }                       ///< 获取首页实例
    DeviceListPage* deviceListPage() const { return m_deviceListPage; }     ///< 获取设备列表页实例
    DeviceConfigPage* deviceConfigPage() const { return m_deviceConfigPage; } ///< 获取设备配置页实例
    MonitorPage* monitorPage() const { return m_monitorPage; }              ///< 获取监控页实例
    DataDetailPage* dataDetailPage() const { return m_dataDetailPage; }     ///< 获取数据详情页实例
    AlarmCenterPage* alarmCenterPage() const { return m_alarmCenterPage; }  ///< 获取告警中心页实例
    AlarmRulePage* alarmRulePage() const { return m_alarmRulePage; }        ///< 获取告警规则页实例
    SettingsPage* settingsPage() const { return m_settingsPage; }           ///< 获取设置页实例
    NetworkPage* networkPage() const { return m_networkPage; }              ///< 获取网络设置页实例
    MqttConfigPage* mqttConfigPage() const { return m_mqttConfigPage; }     ///< 获取MQTT配置页实例
    LogPage* logPage() const { return m_logPage; }                          ///< 获取日志页实例
    HelpPage* helpPage() const { return m_helpPage; }                       ///< 获取帮助页实例

signals:
    /**
     * @brief 页面切换信号
     * @param page 新的当前页面索引
     */
    void pageChanged(PageIndex page);

private:
    /**
     * @brief 初始化界面
     */
    void setupUI();

    /**
     * @brief 创建所有页面
     */
    void createPages();

    /**
     * @brief 连接所有信号槽
     */
    void connectSignals();

    QStackedWidget *m_stackWidget;      ///< 页面堆栈容器
    QStack<PageIndex> m_pageHistory;    ///< 页面历史记录栈

    // 页面实例
    HomePage *m_homePage;               ///< 首页
    DeviceListPage *m_deviceListPage;   ///< 设备列表页
    DeviceConfigPage *m_deviceConfigPage; ///< 设备配置页
    MonitorPage *m_monitorPage;         ///< 实时监控页
    DataDetailPage *m_dataDetailPage;   ///< 数据详情页
    AlarmCenterPage *m_alarmCenterPage; ///< 告警中心页
    AlarmRulePage *m_alarmRulePage;     ///< 告警规则页
    SettingsPage *m_settingsPage;       ///< 系统设置页
    NetworkPage *m_networkPage;         ///< 网络设置页
    MqttConfigPage *m_mqttConfigPage;   ///< MQTT配置页
    LogPage *m_logPage;                 ///< 日志查看页
    HelpPage *m_helpPage;               ///< 帮助页
};

#endif // MAINWINDOW_H
