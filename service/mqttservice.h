#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H

#include "../common/result.h"

struct MqttConfig {
    QString broker;
    int port;
    QString clientId;
    QString username;
    QString password;
    QString topic;
    bool useTls;

    MqttConfig()
        : broker("mqtt.example.com"), port(1883),
          clientId("imx6ull_001"), useTls(false) {}
};

class MqttService
{
public:
    // Load MQTT configuration
    static Result loadMqttConfig();

    // Save MQTT configuration
    static Result saveMqttConfig(const MqttConfig &cfg);

    // Connect to MQTT broker
    static Result connectMqtt();

    // Disconnect from MQTT broker
    static Result disconnectMqtt();

    // Get current connection status
    static Result getMqttStatus();

    // Publish a message
    static Result publish(const QString &topic, const QByteArray &payload);
};

#endif // MQTTSERVICE_H
