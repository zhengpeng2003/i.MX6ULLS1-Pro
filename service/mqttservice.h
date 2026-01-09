/**
 * @file mqttservice.h
 * @brief MQTT服务定义
 *
 * 本文件定义了MQTT云连接相关的服务接口，包括配置加载保存、
 * 连接断开、状态查询、消息发布等功能。
 */

#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H

#include "../common/result.h"

/**
 * @struct MqttConfig
 * @brief MQTT配置结构体
 */
struct MqttConfig {
    QString broker;     ///< MQTT服务器地址
    int port;           ///< 端口号
    QString clientId;   ///< 客户端ID
    QString username;   ///< 用户名
    QString password;   ///< 密码
    QString topic;      ///< 主题
    bool useTls;        ///< 是否使用TLS加密

    MqttConfig()
        : broker("mqtt.example.com"), port(1883),
          clientId("imx6ull_001"), useTls(false) {}
};

/**
 * @class MqttService
 * @brief MQTT服务类
 *
 * 提供MQTT云连接的所有接口，包括配置管理、连接控制、消息发布等。
 */
class MqttService
{
public:
    /**
     * @brief 加载MQTT配置
     * @return Result 包含MQTT配置数据
     */
    static Result loadMqttConfig();

    /**
     * @brief 保存MQTT配置
     * @param cfg MQTT配置参数
     * @return Result 保存结果
     */
    static Result saveMqttConfig(const MqttConfig &cfg);

    /**
     * @brief 连接MQTT服务器
     * @return Result 连接结果
     */
    static Result connectMqtt();

    /**
     * @brief 断开MQTT连接
     * @return Result 断开结果
     */
    static Result disconnectMqtt();

    /**
     * @brief 获取MQTT连接状态
     * @return Result 包含连接状态信息
     */
    static Result getMqttStatus();

    /**
     * @brief 发布消息到指定主题
     * @param topic 主题名称
     * @param payload 消息内容
     * @return Result 发布结果
     */
    static Result publish(const QString &topic, const QByteArray &payload);
};

#endif // MQTTSERVICE_H
