#include "helppage.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

HelpPage::HelpPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QTextEdit *text = new QTextEdit(this);
    text->setReadOnly(true);
    text->setText("工业监控系统使用说明");

    QPushButton *backBtn = new QPushButton("返回", this);

    layout->addWidget(text);
    layout->addWidget(backBtn);

    connect(backBtn, &QPushButton::clicked,
            this, &HelpPage::goBack);
}

