#include "mainwindow.h"
#include "common/appstyle.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set global stylesheet
    a.setStyleSheet(AppStyle::getStyleSheet());

    // Set application properties
    a.setApplicationName("Industrial Monitor System");
    a.setApplicationVersion("1.0.0");

    MainWindow w;
    w.show();

    return a.exec();
}
