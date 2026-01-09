#include "networkpage.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

NetworkPage::NetworkPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *form = new QFormLayout;

    form->addRow("IP地址", new QLineEdit(this));
    form->addRow("子网掩码", new QLineEdit(this));
    form->addRow("网关", new QLineEdit(this));

    QPushButton *saveBtn = new QPushButton("保存", this);
    QPushButton *backBtn = new QPushButton("返回", this);

    mainLayout->addLayout(form);
    mainLayout->addWidget(saveBtn);
    mainLayout->addWidget(backBtn);

    connect(backBtn, &QPushButton::clicked,
            this, &NetworkPage::goBack);
}

