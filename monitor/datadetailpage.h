#ifndef DATADETAILPAGE_H
#define DATADETAILPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QTimer>

class DataDetailPage : public QWidget
{
    Q_OBJECT

public:
    explicit DataDetailPage(QWidget *parent = nullptr);
    ~DataDetailPage();

    void loadData(int deviceId, int addr);

signals:
    void goBack();

private slots:
    void onRefreshTimer();

private:
    void setupUI();
    void setupTitleBar();
    void setupContent();
    void updateData();

    int m_deviceId;
    int m_registerAddr;

    // Title bar
    QWidget *m_titleBar;
    QPushButton *m_backBtn;
    QLabel *m_titleLabel;

    // Value display
    QFrame *m_valueCard;
    QLabel *m_currentValueLabel;
    QLabel *m_unitLabel;
    QLabel *m_updateTimeLabel;

    // Statistics
    QFrame *m_statsCard;
    QLabel *m_minValueLabel;
    QLabel *m_maxValueLabel;
    QLabel *m_avgValueLabel;

    // Chart placeholder
    QFrame *m_chartPlaceholder;
    QLabel *m_chartLabel;

    // Timer
    QTimer *m_refreshTimer;
};

#endif // DATADETAILPAGE_H
