#ifndef LOGPAGE_H
#define LOGPAGE_H

#include <QWidget>

class LogPage : public QWidget
{
    Q_OBJECT
public:
    explicit LogPage(QWidget *parent = nullptr);

signals:
    void goBack();
};

#endif

