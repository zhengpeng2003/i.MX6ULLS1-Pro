#include "logpage.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

LogPage::LogPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QTextEdit *view = new QTextEdit(this);
    view->setReadOnly(true);

    QPushButton *backBtn = new QPushButton("返回", this);

    layout->addWidget(view);
    layout->addWidget(backBtn);

    connect(backBtn, &QPushButton::clicked,
            this, &LogPage::goBack);
}

