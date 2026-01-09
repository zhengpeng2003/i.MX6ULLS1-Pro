#ifndef ALARMRULEPAGE_H
#define ALARMRULEPAGE_H

#include <QWidget>

class AlarmRulePage : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmRulePage(QWidget *parent = nullptr);

signals:
    void goBack();
};

#endif

