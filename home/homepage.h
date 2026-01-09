#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QFrame>

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

    void refreshStatus();

signals:
    void navigateToDevices();
    void navigateToMonitor();
    void navigateToAlarms();
    void navigateToSettings();

private slots:
    void updateTime();
    void onRefreshTimer();

private:
    void setupUI();
    void setupStatusBar();
    void setupStatusCards();
    void setupNavigationButtons();
    void updateStatusCards();

    // Status bar widgets
    QFrame *m_statusBar;
    QLabel *m_timeLabel;
    QLabel *m_networkIcon;
    QLabel *m_rs485Icon;
    QLabel *m_cpuLabel;
    QLabel *m_memLabel;

    // Status cards
    QFrame *m_deviceCard;
    QLabel *m_deviceCountLabel;
    QFrame *m_alarmCard;
    QLabel *m_alarmCountLabel;
    QFrame *m_commCard;
    QLabel *m_commRateLabel;

    // Navigation buttons
    QPushButton *m_deviceBtn;
    QPushButton *m_monitorBtn;
    QPushButton *m_alarmBtn;
    QPushButton *m_settingsBtn;

    // Timers
    QTimer *m_timeTimer;
    QTimer *m_refreshTimer;
};

#endif // HOMEPAGE_H
