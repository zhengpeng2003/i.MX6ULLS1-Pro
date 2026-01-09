/**
 * @file settingspage.h
 * @brief 系统设置页面定义
 *
 * 本文件定义了系统设置页面，作为设置功能的入口，
 * 提供网络设置、MQTT设置、日志查看等子功能的导航。
 */

#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>

/**
 * @class SettingsPage
 * @brief 系统设置页面类
 *
 * 系统设置的主入口页面，提供各子设置页面的导航按钮。
 */
class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit SettingsPage(QWidget *parent = nullptr);

signals:
    void goBack();              ///< 返回上一页信号
    void navigateToNetwork();   ///< 跳转到网络设置页面信号
    void navigateToMqtt();      ///< 跳转到MQTT设置页面信号
    void navigateToLog();       ///< 跳转到日志查看页面信号
    void navigateToHelp();      ///< 跳转到帮助页面信号
};

#endif // SETTINGSPAGE_H
