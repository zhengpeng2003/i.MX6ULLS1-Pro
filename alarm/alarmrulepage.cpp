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

    QLabel *title = new QLabel("告警规则配置", this);
    title->setAlignment(Qt::AlignCenter);

    QFormLayout *form = new QFormLayout;
    form->addRow("上限阈值", new QLineEdit(this));
    form->addRow("下限阈值", new QLineEdit(this));
    form->addRow("通信超时(ms)", new QLineEdit(this));

    QPushButton *saveBtn = new QPushButton("保存", this);
    QPushButton *backBtn = new QPushButton("返回", this);

    mainLayout->addWidget(title);
    mainLayout->addLayout(form);
    mainLayout->addWidget(saveBtn);
    mainLayout->addWidget(backBtn);

    connect(backBtn, &QPushButton::clicked,
            this, &AlarmRulePage::goBack);
}

