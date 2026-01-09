/**
 * @file main.cpp
 * @brief 程序入口
 *
 * 本文件是应用程序的入口点，负责初始化Qt应用程序、
 * 设置全局样式表并启动主窗口。
 */

#include "mainwindow.h"
#include "common/appstyle.h"

#include <QApplication>

/**
 * @brief 程序主入口函数
 * @param argc 命令行参数个数
 * @param argv 命令行参数数组
 * @return 程序退出码
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置全局样式表
    a.setStyleSheet(AppStyle::getStyleSheet());

    // 设置应用程序属性
    a.setApplicationName("工业监控系统");
    a.setApplicationVersion("1.0.0");

    // 创建并显示主窗口
    MainWindow w;
    w.show();

    return a.exec();
}
