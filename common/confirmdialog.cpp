/**
 * @file confirmdialog.cpp
 * @brief 确认对话框组件实现
 *
 * 本文件实现了确认对话框的所有功能，包括界面布局、按钮事件等。
 */

#include "confirmdialog.h"
#include "appstyle.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ConfirmDialog::ConfirmDialog(QWidget *parent)
    : QDialog(parent)
    , m_titleLabel(new QLabel(this))
    , m_messageLabel(new QLabel(this))
    , m_confirmBtn(new QPushButton(this))
    , m_cancelBtn(new QPushButton(this))
{
    setupUI();
}

ConfirmDialog::~ConfirmDialog()
{
}

void ConfirmDialog::setupUI()
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setModal(true);
    setFixedSize(320, 180);

    setStyleSheet(
        "QDialog {"
        "   background-color: #16213e;"
        "   border: 2px solid #0f3460;"
        "   border-radius: 10px;"
        "}"
    );

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 15, 20, 15);
    mainLayout->setSpacing(12);

    // 标题
    m_titleLabel->setStyleSheet(
        "QLabel {"
        "   color: #ffffff;"
        "   font-size: 16pt;"
        "   font-weight: bold;"
        "   background: transparent;"
        "}"
    );
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setText("确认");
    mainLayout->addWidget(m_titleLabel);

    // 消息内容
    m_messageLabel->setStyleSheet(
        "QLabel {"
        "   color: #a0a0a0;"
        "   font-size: 12pt;"
        "   background: transparent;"
        "}"
    );
    m_messageLabel->setAlignment(Qt::AlignCenter);
    m_messageLabel->setWordWrap(true);
    mainLayout->addWidget(m_messageLabel);

    mainLayout->addStretch();

    // 按钮区域
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    m_cancelBtn->setText("取消");
    m_cancelBtn->setMinimumHeight(44);
    m_cancelBtn->setStyleSheet(AppStyle::getButtonStyle(false));
    connect(m_cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    btnLayout->addWidget(m_cancelBtn);

    m_confirmBtn->setText("确认");
    m_confirmBtn->setMinimumHeight(44);
    m_confirmBtn->setStyleSheet(AppStyle::getButtonStyle(true));
    connect(m_confirmBtn, &QPushButton::clicked, this, &QDialog::accept);
    btnLayout->addWidget(m_confirmBtn);

    mainLayout->addLayout(btnLayout);
}

void ConfirmDialog::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
}

void ConfirmDialog::setMessage(const QString &message)
{
    m_messageLabel->setText(message);
}

void ConfirmDialog::setConfirmText(const QString &text)
{
    m_confirmBtn->setText(text);
}

void ConfirmDialog::setCancelText(const QString &text)
{
    m_cancelBtn->setText(text);
}

bool ConfirmDialog::confirm(QWidget *parent, const QString &title, const QString &message)
{
    ConfirmDialog dialog(parent);
    dialog.setTitle(title);
    dialog.setMessage(message);

    // 居中显示在父窗口上
    if (parent) {
        QPoint center = parent->mapToGlobal(parent->rect().center());
        dialog.move(center.x() - dialog.width() / 2, center.y() - dialog.height() / 2);
    }

    return dialog.exec() == QDialog::Accepted;
}

bool ConfirmDialog::confirm(QWidget *parent, const QString &message)
{
    return confirm(parent, "确认", message);
}
