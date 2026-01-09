#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>

class SettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsPage(QWidget *parent = nullptr);

signals:
    void goBack();
    void navigateToNetwork();
    void navigateToMqtt();
    void navigateToLog();
    void navigateToHelp();
};

#endif

