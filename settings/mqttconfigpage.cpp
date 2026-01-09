#include "mqttconfigpage.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

MqttConfigPage::MqttConfigPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *form = new QFormLayout;

    form->addRow("服务器地址", new QLineEdit(this));
    form->addRow("端口", new QLineEdit(this));
    form->addRow("主题", new QLineEdit(this));

    QPushButton *saveBtn = new QPushButton("保存", this);
    QPushButton *backBtn = new QPushButton("返回", this);

    mainLayout->addLayout(form);
    mainLayout->addWidget(saveBtn);
    mainLayout->addWidget(backBtn);

    connect(backBtn, &QPushButton::clicked,
            this, &MqttConfigPage::goBack);
}

