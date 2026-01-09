#include "alarmcenterpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>

AlarmCenterPage::AlarmCenterPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("告警中心", this);
    title->setAlignment(Qt::AlignCenter);

    m_table = new QTableWidget(0, 5, this);
    m_table->setHorizontalHeaderLabels(
        {"时间", "设备", "类型", "级别", "状态"}
    );
    m_table->horizontalHeader()->setStretchLastSection(true);

    m_backBtn = new QPushButton("返回", this);
    m_ruleBtn = new QPushButton("告警规则", this);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_backBtn);
    btnLayout->addWidget(m_ruleBtn);

    mainLayout->addWidget(title);
    mainLayout->addWidget(m_table);
    mainLayout->addLayout(btnLayout);

    connect(m_backBtn, &QPushButton::clicked,
            this, &AlarmCenterPage::goBack);
    connect(m_ruleBtn, &QPushButton::clicked,
            this, &AlarmCenterPage::configureRules);
}

