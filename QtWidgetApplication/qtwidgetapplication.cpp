#include "qtwidgetapplication.h"
#include "./ui_qtwidgetapplication.h"

QtWidgetApplication::QtWidgetApplication(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtWidgetApplication)
{
    ui->setupUi(this);
}

QtWidgetApplication::~QtWidgetApplication()
{
    delete ui;
}
