#ifndef MONITORPAGE_H
#define MONITORPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTimer>

class MonitorPage : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorPage(QWidget *parent = nullptr);
    ~MonitorPage();

signals:
    void goBack();
    void viewDetail(int deviceId, int addr);

private slots:
    void onDeviceChanged(int index);
    void onStartStopClicked();
    void onPollTimer();
    void onTableDoubleClicked(int row, int column);

private:
    void setupUI();
    void setupTitleBar();
    void setupControls();
    void setupTable();
    void loadDevices();
    void updateData();
    void setPollingState(bool polling);

    // Title bar
    QWidget *m_titleBar;
    QPushButton *m_backBtn;
    QLabel *m_titleLabel;

    // Controls
    QComboBox *m_deviceCombo;
    QPushButton *m_startStopBtn;
    QLabel *m_statusLed;
    QLabel *m_statusLabel;

    // Table
    QTableWidget *m_table;

    // Timer
    QTimer *m_pollTimer;
    bool m_isPolling;
    int m_currentDeviceId;
};

#endif // MONITORPAGE_H
