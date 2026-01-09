/**
 * @file helppage.h
 * @brief 帮助页面定义
 *
 * 本文件定义了帮助页面，用于显示系统使用说明和帮助文档，
 * 帮助用户了解系统功能和操作方法。
 */

#ifndef HELPPAGE_H
#define HELPPAGE_H

#include <QWidget>

/**
 * @class HelpPage
 * @brief 帮助页面类
 *
 * 显示系统帮助文档和使用说明。
 */
class HelpPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit HelpPage(QWidget *parent = nullptr);

signals:
    void goBack();  ///< 返回上一页信号
};

#endif // HELPPAGE_H
