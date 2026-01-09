/**
 * @file alarmcenterpage.cpp
 * @brief 告警中心页面实现
 *
 * 本文件实现了告警中心页面的所有功能，包括告警列表显示、
 * 告警状态管理和规则配置入口。
 */

#include "alarmcenterpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>

AlarmCenterPage::AlarmCenterPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 页面标题
    QLabel *title = new QLabel("告警中心", this);
    title->setAlignment(Qt::AlignCenter);

    // 告警列表表格
    m_table = new QTableWidget(0, 5, this);
    m_table->setHorizontalHeaderLabels(
        {"时间", "设备", "类型", "级别", "状态"}
    );
    m_table->horizontalHeader()->setStretchLastSection(true);

    // 底部按钮
    m_backBtn = new QPushButton("返回", this);
    m_ruleBtn = new QPushButton("告警规则", this);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_backBtn);
    btnLayout->addWidget(m_ruleBtn);

    mainLayout->addWidget(title);
    mainLayout->addWidget(m_table);
    mainLayout->addLayout(btnLayout);

    // 信号连接
    connect(m_backBtn, &QPushButton::clicked,
            this, &AlarmCenterPage::goBack);
    connect(m_ruleBtn, &QPushButton::clicked,
            this, &AlarmCenterPage::configureRules);
}
