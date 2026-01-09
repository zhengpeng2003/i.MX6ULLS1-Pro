#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDialog(QWidget *parent = nullptr);
    ~ConfirmDialog();

    void setTitle(const QString &title);
    void setMessage(const QString &message);
    void setConfirmText(const QString &text);
    void setCancelText(const QString &text);

    static bool confirm(QWidget *parent, const QString &title, const QString &message);
    static bool confirm(QWidget *parent, const QString &message);

private:
    void setupUI();

    QLabel *m_titleLabel;
    QLabel *m_messageLabel;
    QPushButton *m_confirmBtn;
    QPushButton *m_cancelBtn;
};

#endif // CONFIRMDIALOG_H
