/**
 * @file toast.cpp
 * @brief 轻提示组件实现
 *
 * 本文件实现了Toast轻提示组件的所有功能，包括显示、动画、自动消失等。
 */

#include "toast.h"
#include <QPainter>
#include <QApplication>

Toast::Toast(QWidget *parent)
    : QWidget(parent)
    , m_label(new QLabel(this))
    , m_timer(new QTimer(this))
    , m_animation(new QPropertyAnimation(this, "opacity"))
    , m_opacity(1.0)
    , m_type(Info)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    m_label->setAlignment(Qt::AlignCenter);
    m_label->setStyleSheet("QLabel { color: #ffffff; font-size: 12pt; background: transparent; }");

    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &Toast::fadeOut);

    m_animation->setDuration(300);
    connect(m_animation, &QPropertyAnimation::finished, this, &Toast::deleteLater);
}

Toast::~Toast()
{
}

void Toast::show(QWidget *parent, const QString &message, Type type, int duration)
{
    Toast *toast = new Toast(parent);
    toast->showToast(message, type, duration);
}

void Toast::showInfo(QWidget *parent, const QString &message, int duration)
{
    show(parent, message, Info, duration);
}

void Toast::showSuccess(QWidget *parent, const QString &message, int duration)
{
    show(parent, message, Success, duration);
}

void Toast::showWarning(QWidget *parent, const QString &message, int duration)
{
    show(parent, message, Warning, duration);
}

void Toast::showError(QWidget *parent, const QString &message, int duration)
{
    show(parent, message, Error, duration);
}

void Toast::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    update();
}

void Toast::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setOpacity(m_opacity);

    QColor bgColor;
    switch (m_type) {
    case Success:
        bgColor = QColor("#00884480");
        break;
    case Warning:
        bgColor = QColor("#aa660080");
        break;
    case Error:
        bgColor = QColor("#aa222280");
        break;
    default:
        bgColor = QColor("#0f346080");
        break;
    }

    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 8, 8);

    // Draw border
    QColor borderColor;
    switch (m_type) {
    case Success:
        borderColor = QColor("#00ff88");
        break;
    case Warning:
        borderColor = QColor("#ffaa00");
        break;
    case Error:
        borderColor = QColor("#ff4444");
        break;
    default:
        borderColor = QColor("#e94560");
        break;
    }

    painter.setPen(QPen(borderColor, 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 8, 8);
}

void Toast::showToast(const QString &message, Type type, int duration)
{
    m_type = type;
    m_label->setText(message);

    // Calculate size
    QFontMetrics fm(m_label->font());
    int textWidth = fm.horizontalAdvance(message) + 40;
    int textHeight = fm.height() + 20;

    int width = qMin(textWidth, 400);
    int height = qMax(textHeight, 48);

    setFixedSize(width, height);
    m_label->setGeometry(0, 0, width, height);

    // Position at bottom center of parent
    if (parentWidget()) {
        QPoint parentCenter = parentWidget()->mapToGlobal(parentWidget()->rect().center());
        int x = parentCenter.x() - width / 2;
        int y = parentWidget()->mapToGlobal(QPoint(0, 0)).y() + parentWidget()->height() - height - 60;
        move(x, y);
    }

    QWidget::show();
    m_timer->start(duration);
}

void Toast::fadeOut()
{
    m_animation->setStartValue(1.0);
    m_animation->setEndValue(0.0);
    m_animation->start();
}
