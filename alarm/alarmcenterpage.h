/**
 * @file alarmcenterpage.h
 * @brief 告警中心页面定义
 *
 * 本文件定义了告警中心页面，用于显示当前活动告警列表，
 * 支持查看告警详情和跳转到告警规则配置。
 */

#ifndef ALARMCENTERPAGE_H
#define ALARMCENTERPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

/**
 * @class AlarmCenterPage
 * @brief 告警中心页面类
 *
 * 显示系统中所有活动告警，提供告警确认和规则配置入口。
 */
class AlarmCenterPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit AlarmCenterPage(QWidget *parent = nullptr);

signals:
    void goBack();          ///< 返回上一页信号
    void configureRules();  ///< 配置告警规则信号

private:
    QTableWidget *m_table;      ///< 告警列表表格
    QPushButton *m_backBtn;     ///< 返回按钮
    QPushButton *m_ruleBtn;     ///< 告警规则按钮
};

#endif // ALARMCENTERPAGE_H
