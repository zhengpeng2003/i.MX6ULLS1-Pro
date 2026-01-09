#ifndef NETWORKPAGE_H
#define NETWORKPAGE_H

#include <QWidget>

class NetworkPage : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkPage(QWidget *parent = nullptr);

signals:
    void goBack();
};

#endif

