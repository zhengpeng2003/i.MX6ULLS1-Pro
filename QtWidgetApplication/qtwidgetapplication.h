#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtWidgetApplication;
}
QT_END_NAMESPACE

class QtWidgetApplication : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetApplication(QWidget *parent = nullptr);
    ~QtWidgetApplication();

private:
    Ui::QtWidgetApplication *ui;
};
