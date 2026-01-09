#ifndef ALARMCENTERPAGE_H
#define ALARMCENTERPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

class AlarmCenterPage : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmCenterPage(QWidget *parent = nullptr);

signals:
    void goBack();
    void configureRules();

private:
    QTableWidget *m_table;
    QPushButton *m_backBtn;
    QPushButton *m_ruleBtn;
};

#endif

