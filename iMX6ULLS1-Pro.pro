QT += core gui network widgets
CONFIG += c++17

# 目标文件名
TARGET = iMX6ULLS1-Pro

# 主窗口文件
SOURCES += main.cpp \
           alarm/alarmcenterpage.cpp \
           alarm/alarmrulepage.cpp \
           help/helppage.cpp \
           mainwindow.cpp \
           settings/logpage.cpp \
           settings/mqttconfigpage.cpp \
           settings/networkpage.cpp \
           settings/settingspage.cpp

HEADERS += mainwindow.h \
    alarm/alarmcenterpage.h \
    alarm/alarmrulepage.h \
    help/helppage.h \
    settings/logpage.h \
    settings/mqttconfigpage.h \
    settings/networkpage.h \
    settings/settingspage.h
FORMS += mainwindow.ui

# Common目录
SOURCES += common/appstyle.cpp \
           common/confirmdialog.cpp \
           common/toast.cpp

HEADERS += common/appstyle.h \
           common/confirmdialog.h \
           common/result.h \
           common/toast.h

# Device目录
SOURCES += device/deviceconfigpage.cpp \
           device/devicelistpage.cpp

HEADERS += device/deviceconfigpage.h \
           device/devicelistpage.h

# Home目录
SOURCES += home/homepage.cpp
HEADERS += home/homepage.h

# Monitor目录
SOURCES += monitor/datadetailpage.cpp \
           monitor/monitorpage.cpp

HEADERS += monitor/datadetailpage.h \
           monitor/monitorpage.h

# Service目录
SOURCES += service/alarmservice.cpp \
           service/deviceservice.cpp \
           service/modbusservice.cpp \
           service/mqttservice.cpp \
           service/networkservice.cpp \
           service/systemservice.cpp

HEADERS += service/alarmservice.h \
           service/deviceservice.h \
           service/modbusservice.h \
           service/mqttservice.h \
           service/networkservice.h \
           service/systemservice.h

# 包含路径
INCLUDEPATH += . \
               common \
               device \
               home \
               monitor \
               service

# 去掉有问题的DESTDIR设置，让qmake自动处理
# 或者只设置中间文件目录
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui

# 部署配置（可选）
# target.path = /opt/$${TARGET}/bin
# INSTALLS += target
