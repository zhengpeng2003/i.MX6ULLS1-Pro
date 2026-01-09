#ifndef DEVICESERVICE_H
#define DEVICESERVICE_H

#include "../common/result.h"

struct DeviceConfig {
    int id;
    int modbusAddress;
    int functionCode;
    int startAddress;
    int registerCount;
    int pollInterval;       // milliseconds
    QString name;
    QString type;
    QString remark;
    bool enabled;

    DeviceConfig()
        : id(-1), modbusAddress(1), functionCode(3), startAddress(0),
          registerCount(10), pollInterval(1000), enabled(true) {}
};

class DeviceService
{
public:
    // Get list of all devices
    static Result getDeviceList();

    // Add a new device
    static Result addDevice(const DeviceConfig &cfg);

    // Update device configuration
    static Result updateDevice(int id, const DeviceConfig &cfg);

    // Remove device
    static Result removeDevice(int id);

    // Scan for Modbus devices
    static Result scanModbusDevices();

    // Load device configuration
    static Result loadDeviceConfig(int id);

    // Save device configuration
    static Result saveDeviceConfig(int id, const DeviceConfig &cfg);

    // Validate configuration
    static Result validateConfig(const DeviceConfig &cfg);
};

#endif // DEVICESERVICE_H
