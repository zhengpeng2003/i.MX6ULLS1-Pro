/**
 * @file helppage.cpp
 * @brief 帮助页面实现
 *
 * 本文件实现了帮助页面的所有功能，包括帮助文档的加载和显示。
 */

#include "helppage.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

HelpPage::HelpPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 帮助文档显示区域
    QTextEdit *text = new QTextEdit(this);
    text->setReadOnly(true);
    text->setText("工业监控系统使用说明");

    // 返回按钮
    QPushButton *backBtn = new QPushButton("返回", this);

    layout->addWidget(text);
    layout->addWidget(backBtn);

    // 信号连接
    connect(backBtn, &QPushButton::clicked,
            this, &HelpPage::goBack);
}
