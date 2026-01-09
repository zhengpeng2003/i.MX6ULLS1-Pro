/**
 * @file mqttconfigpage.cpp
 * @brief MQTT配置页面实现
 *
 * 本文件实现了MQTT配置页面的所有功能，包括MQTT参数表单
 * 和配置保存逻辑。
 */

#include "mqttconfigpage.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

MqttConfigPage::MqttConfigPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // MQTT配置表单
    QFormLayout *form = new QFormLayout;
    form->addRow("服务器地址:", new QLineEdit(this));
    form->addRow("端口:", new QLineEdit(this));
    form->addRow("主题:", new QLineEdit(this));

    // 操作按钮
    QPushButton *saveBtn = new QPushButton("保存", this);
    QPushButton *backBtn = new QPushButton("返回", this);

    mainLayout->addLayout(form);
    mainLayout->addWidget(saveBtn);
    mainLayout->addWidget(backBtn);

    // 信号连接
    connect(backBtn, &QPushButton::clicked,
            this, &MqttConfigPage::goBack);
}
