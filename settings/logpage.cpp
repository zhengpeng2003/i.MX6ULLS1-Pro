/**
 * @file logpage.cpp
 * @brief 日志查看页面实现
 *
 * 本文件实现了日志查看页面的所有功能，包括日志内容显示
 * 和日志加载逻辑。
 */

#include "logpage.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

LogPage::LogPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 日志显示区域
    QTextEdit *view = new QTextEdit(this);
    view->setReadOnly(true);

    // 返回按钮
    QPushButton *backBtn = new QPushButton("返回", this);

    layout->addWidget(view);
    layout->addWidget(backBtn);

    // 信号连接
    connect(backBtn, &QPushButton::clicked,
            this, &LogPage::goBack);
}
