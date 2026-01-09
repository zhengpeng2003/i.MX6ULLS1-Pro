#ifndef MQTTCONFIGPAGE_H
#define MQTTCONFIGPAGE_H

#include <QWidget>

class MqttConfigPage : public QWidget
{
    Q_OBJECT
public:
    explicit MqttConfigPage(QWidget *parent = nullptr);

signals:
    void goBack();
};

#endif

