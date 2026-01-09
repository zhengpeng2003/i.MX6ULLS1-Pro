/**
 * @file alarmrulepage.h
 * @brief 告警规则配置页面定义
 *
 * 本文件定义了告警规则配置页面，用于设置告警阈值、
 * 通信超时等告警触发条件。
 */

#ifndef ALARMRULEPAGE_H
#define ALARMRULEPAGE_H

#include <QWidget>

/**
 * @class AlarmRulePage
 * @brief 告警规则配置页面类
 *
 * 提供告警规则的配置界面，包括阈值设置和超时设置。
 */
class AlarmRulePage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit AlarmRulePage(QWidget *parent = nullptr);

signals:
    void goBack();  ///< 返回上一页信号
};

#endif // ALARMRULEPAGE_H
