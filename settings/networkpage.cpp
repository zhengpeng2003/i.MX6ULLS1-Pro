/**
 * @file networkpage.cpp
 * @brief 网络设置页面实现
 *
 * 本文件实现了网络设置页面的所有功能，包括网络参数表单
 * 和配置保存逻辑。
 */

#include "networkpage.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

NetworkPage::NetworkPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 网络配置表单
    QFormLayout *form = new QFormLayout;
    form->addRow("IP地址:", new QLineEdit(this));
    form->addRow("子网掩码:", new QLineEdit(this));
    form->addRow("网关:", new QLineEdit(this));

    // 操作按钮
    QPushButton *saveBtn = new QPushButton("保存", this);
    QPushButton *backBtn = new QPushButton("返回", this);

    mainLayout->addLayout(form);
    mainLayout->addWidget(saveBtn);
    mainLayout->addWidget(backBtn);

    // 信号连接
    connect(backBtn, &QPushButton::clicked,
            this, &NetworkPage::goBack);
}
