#ifndef TOAST_H
#define TOAST_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>

class Toast : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    enum Type {
        Info,
        Success,
        Warning,
        Error
    };

    explicit Toast(QWidget *parent = nullptr);
    ~Toast();

    static void show(QWidget *parent, const QString &message, Type type = Info, int duration = 2000);
    static void showInfo(QWidget *parent, const QString &message, int duration = 2000);
    static void showSuccess(QWidget *parent, const QString &message, int duration = 2000);
    static void showWarning(QWidget *parent, const QString &message, int duration = 2000);
    static void showError(QWidget *parent, const QString &message, int duration = 2000);

    qreal opacity() const { return m_opacity; }
    void setOpacity(qreal opacity);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void showToast(const QString &message, Type type, int duration);
    void fadeOut();

    QLabel *m_label;
    QTimer *m_timer;
    QPropertyAnimation *m_animation;
    qreal m_opacity;
    Type m_type;
};

#endif // TOAST_H
