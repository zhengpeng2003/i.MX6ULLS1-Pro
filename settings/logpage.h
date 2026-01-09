/**
 * @file logpage.h
 * @brief 日志查看页面定义
 *
 * 本文件定义了日志查看页面，用于显示系统运行日志，
 * 方便用户排查问题和了解系统运行状态。
 */

#ifndef LOGPAGE_H
#define LOGPAGE_H

#include <QWidget>

/**
 * @class LogPage
 * @brief 日志查看页面类
 *
 * 显示系统日志内容，支持滚动查看。
 */
class LogPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit LogPage(QWidget *parent = nullptr);

signals:
    void goBack();  ///< 返回上一页信号
};

#endif // LOGPAGE_H
