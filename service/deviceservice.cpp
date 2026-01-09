#include "deviceservice.h"

// Static mock device list
static QVariantList s_deviceList;
static int s_nextDeviceId = 1;
static bool s_initialized = false;

static void initMockData()
{
    if (s_initialized) return;
    s_initialized = true;

    // Add some mock devices
    QVariantMap dev1;
    dev1["id"] = s_nextDeviceId++;
    dev1["modbusAddress"] = 1;
    dev1["name"] = "Temperature Sensor";
    dev1["type"] = "Sensor";
    dev1["status"] = "Online";
    dev1["online"] = true;
    dev1["functionCode"] = 3;
    dev1["startAddress"] = 0;
    dev1["registerCount"] = 10;
    dev1["pollInterval"] = 1000;
    s_deviceList.append(dev1);

    QVariantMap dev2;
    dev2["id"] = s_nextDeviceId++;
    dev2["modbusAddress"] = 2;
    dev2["name"] = "Pressure Gauge";
    dev2["type"] = "Sensor";
    dev2["status"] = "Online";
    dev2["online"] = true;
    dev2["functionCode"] = 3;
    dev2["startAddress"] = 0;
    dev2["registerCount"] = 5;
    dev2["pollInterval"] = 2000;
    s_deviceList.append(dev2);

    QVariantMap dev3;
    dev3["id"] = s_nextDeviceId++;
    dev3["modbusAddress"] = 3;
    dev3["name"] = "Flow Meter";
    dev3["type"] = "Meter";
    dev3["status"] = "Offline";
    dev3["online"] = false;
    dev3["functionCode"] = 4;
    dev3["startAddress"] = 100;
    dev3["registerCount"] = 8;
    dev3["pollInterval"] = 1500;
    s_deviceList.append(dev3);
}

Result DeviceService::getDeviceList()
{
    initMockData();
    return Result::success(s_deviceList);
}

Result DeviceService::addDevice(const DeviceConfig &cfg)
{
    initMockData();

    QVariantMap dev;
    dev["id"] = s_nextDeviceId++;
    dev["modbusAddress"] = cfg.modbusAddress;
    dev["name"] = cfg.name;
    dev["type"] = cfg.type;
    dev["status"] = "Unknown";
    dev["online"] = false;
    dev["functionCode"] = cfg.functionCode;
    dev["startAddress"] = cfg.startAddress;
    dev["registerCount"] = cfg.registerCount;
    dev["pollInterval"] = cfg.pollInterval;
    dev["remark"] = cfg.remark;

    s_deviceList.append(dev);
    return Result::success(dev["id"]);
}

Result DeviceService::updateDevice(int id, const DeviceConfig &cfg)
{
    initMockData();

    for (int i = 0; i < s_deviceList.size(); ++i) {
        QVariantMap dev = s_deviceList[i].toMap();
        if (dev["id"].toInt() == id) {
            dev["modbusAddress"] = cfg.modbusAddress;
            dev["name"] = cfg.name;
            dev["type"] = cfg.type;
            dev["functionCode"] = cfg.functionCode;
            dev["startAddress"] = cfg.startAddress;
            dev["registerCount"] = cfg.registerCount;
            dev["pollInterval"] = cfg.pollInterval;
            dev["remark"] = cfg.remark;
            s_deviceList[i] = dev;
            return Result::success();
        }
    }
    return Result::error(404, "Device not found");
}

Result DeviceService::removeDevice(int id)
{
    initMockData();

    for (int i = 0; i < s_deviceList.size(); ++i) {
        if (s_deviceList[i].toMap()["id"].toInt() == id) {
            s_deviceList.removeAt(i);
            return Result::success();
        }
    }
    return Result::error(404, "Device not found");
}

Result DeviceService::scanModbusDevices()
{
    // Mock scan - returns list of found addresses
    QVariantList found;
    found << 1 << 2 << 5 << 10;
    return Result::success(found);
}

Result DeviceService::loadDeviceConfig(int id)
{
    initMockData();

    for (const QVariant &v : s_deviceList) {
        QVariantMap dev = v.toMap();
        if (dev["id"].toInt() == id) {
            return Result::success(dev);
        }
    }
    return Result::error(404, "Device not found");
}

Result DeviceService::saveDeviceConfig(int id, const DeviceConfig &cfg)
{
    if (id < 0) {
        return addDevice(cfg);
    }
    return updateDevice(id, cfg);
}

Result DeviceService::validateConfig(const DeviceConfig &cfg)
{
    if (cfg.modbusAddress < 1 || cfg.modbusAddress > 247) {
        return Result::error(1, "Modbus address must be 1-247");
    }
    if (cfg.functionCode < 1 || cfg.functionCode > 6) {
        return Result::error(2, "Invalid function code");
    }
    if (cfg.startAddress < 0 || cfg.startAddress > 65535) {
        return Result::error(3, "Invalid start address");
    }
    if (cfg.registerCount < 1 || cfg.registerCount > 125) {
        return Result::error(4, "Register count must be 1-125");
    }
    if (cfg.pollInterval < 100 || cfg.pollInterval > 60000) {
        return Result::error(5, "Poll interval must be 100-60000ms");
    }
    return Result::success();
}
