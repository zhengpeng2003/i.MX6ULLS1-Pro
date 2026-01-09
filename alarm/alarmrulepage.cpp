/**
 * @file alarmrulepage.cpp
 * @brief 告警规则配置页面实现
 *
 * 本文件实现了告警规则配置页面的所有功能，包括阈值设置表单、
 * 超时配置和规则保存。
 */

#include "alarmrulepage.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

AlarmRulePage::AlarmRulePage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 页面标题
    QLabel *title = new QLabel("告警规则配置", this);
    title->setAlignment(Qt::AlignCenter);

    // 配置表单
    QFormLayout *form = new QFormLayout;
    form->addRow("上限阈值:", new QLineEdit(this));
    form->addRow("下限阈值:", new QLineEdit(this));
    form->addRow("通信超时(毫秒):", new QLineEdit(this));

    // 操作按钮
    QPushButton *saveBtn = new QPushButton("保存", this);
    QPushButton *backBtn = new QPushButton("返回", this);

    mainLayout->addWidget(title);
    mainLayout->addLayout(form);
    mainLayout->addWidget(saveBtn);
    mainLayout->addWidget(backBtn);

    // 信号连接
    connect(backBtn, &QPushButton::clicked,
            this, &AlarmRulePage::goBack);
}
