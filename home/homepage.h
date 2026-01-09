/**
 * @file homepage.h
 * @brief 系统首页定义
 *
 * 本文件定义了工业设备监控系统的主页面，显示顶部状态栏（时间、网络状态、
 * RS485状态、CPU/内存使用率），中部状态卡片（在线设备数、告警数、通信正常率），
 * 以及导航按钮（设备管理、实时监控、告警中心、系统设置）。
 */

#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QFrame>

/**
 * @class HomePage
 * @brief 系统首页类
 *
 * 显示系统概览信息和主要功能入口。
 */
class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

    /**
     * @brief 刷新首页上所有状态信息
     */
    void refreshStatus();

signals:
    void navigateToDevices();   ///< 跳转到设备管理页面
    void navigateToMonitor();   ///< 跳转到实时监控页面
    void navigateToAlarms();    ///< 跳转到告警中心页面
    void navigateToSettings();  ///< 跳转到系统设置页面

private slots:
    void updateTime();          ///< 更新时间显示
    void onRefreshTimer();      ///< 定时刷新状态

private:
    void setupUI();
    void setupStatusBar();
    void setupStatusCards();
    void setupNavigationButtons();
    void updateStatusCards();

    // 状态栏控件
    QFrame *m_statusBar;        ///< 状态栏容器
    QLabel *m_timeLabel;        ///< 时间标签
    QLabel *m_networkIcon;      ///< 网络状态图标
    QLabel *m_rs485Icon;        ///< RS485状态图标
    QLabel *m_cpuLabel;         ///< CPU使用率标签
    QLabel *m_memLabel;         ///< 内存使用率标签

    // 状态卡片
    QFrame *m_deviceCard;       ///< 设备卡片
    QLabel *m_deviceCountLabel; ///< 在线设备数量标签
    QFrame *m_alarmCard;        ///< 告警卡片
    QLabel *m_alarmCountLabel;  ///< 告警数量标签
    QFrame *m_commCard;         ///< 通信卡片
    QLabel *m_commRateLabel;    ///< 通信正常率标签

    // 导航按钮
    QPushButton *m_deviceBtn;   ///< 设备管理按钮
    QPushButton *m_monitorBtn;  ///< 实时监控按钮
    QPushButton *m_alarmBtn;    ///< 告警中心按钮
    QPushButton *m_settingsBtn; ///< 系统设置按钮

    // 定时器
    QTimer *m_timeTimer;        ///< 时间更新定时器
    QTimer *m_refreshTimer;     ///< 状态刷新定时器
};

#endif // HOMEPAGE_H
