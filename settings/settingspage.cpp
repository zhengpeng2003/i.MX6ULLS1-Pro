/**
 * @file settingspage.cpp
 * @brief 系统设置页面实现
 *
 * 本文件实现了系统设置页面的所有功能，包括设置菜单按钮的创建
 * 和各子页面的导航逻辑。
 */

#include "settingspage.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 页面标题
    QLabel *title = new QLabel("系统设置", this);
    title->setAlignment(Qt::AlignCenter);

    // 功能按钮
    QPushButton *netBtn  = new QPushButton("网络设置", this);
    QPushButton *mqttBtn = new QPushButton("MQTT设置", this);
    QPushButton *logBtn  = new QPushButton("日志查看", this);
    QPushButton *helpBtn = new QPushButton("帮助", this);
    QPushButton *backBtn = new QPushButton("返回", this);

    layout->addWidget(title);
    layout->addWidget(netBtn);
    layout->addWidget(mqttBtn);
    layout->addWidget(logBtn);
    layout->addWidget(helpBtn);
    layout->addWidget(backBtn);

    // 信号连接
    connect(netBtn,  &QPushButton::clicked, this, &SettingsPage::navigateToNetwork);
    connect(mqttBtn, &QPushButton::clicked, this, &SettingsPage::navigateToMqtt);
    connect(logBtn,  &QPushButton::clicked, this, &SettingsPage::navigateToLog);
    connect(helpBtn, &QPushButton::clicked, this, &SettingsPage::navigateToHelp);
    connect(backBtn, &QPushButton::clicked, this, &SettingsPage::goBack);
}
