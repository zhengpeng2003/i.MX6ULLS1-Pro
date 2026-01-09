/**
 * @file mqttconfigpage.h
 * @brief MQTT配置页面定义
 *
 * 本文件定义了MQTT配置页面，用于配置MQTT云端连接参数，
 * 包括服务器地址、端口和主题设置。
 */

#ifndef MQTTCONFIGPAGE_H
#define MQTTCONFIGPAGE_H

#include <QWidget>

/**
 * @class MqttConfigPage
 * @brief MQTT配置页面类
 *
 * 提供MQTT连接参数配置界面，支持云端数据上传设置。
 */
class MqttConfigPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit MqttConfigPage(QWidget *parent = nullptr);

signals:
    void goBack();  ///< 返回上一页信号
};

#endif // MQTTCONFIGPAGE_H
