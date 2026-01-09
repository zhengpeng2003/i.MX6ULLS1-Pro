/**
 * @file deviceservice.cpp
 * @brief 设备服务实现
 *
 * 本文件实现了设备管理服务的所有功能，包括设备的增删改查、
 * 扫描设备、配置校验等。当前为模拟数据，实际部署时需替换为真实数据存储。
 */

#include "deviceservice.h"

// 静态模拟设备列表
static QVariantList s_deviceList;
static int s_nextDeviceId = 1;
static bool s_initialized = false;

/**
 * @brief 初始化模拟数据
 */
static void initMockData()
{
    if (s_initialized) return;
    s_initialized = true;

    // 添加模拟设备
    QVariantMap dev1;
    dev1["id"] = s_nextDeviceId++;
    dev1["modbusAddress"] = 1;
    dev1["name"] = "温度传感器";
    dev1["type"] = "传感器";
    dev1["status"] = "在线";
    dev1["online"] = true;
    dev1["functionCode"] = 3;
    dev1["startAddress"] = 0;
    dev1["registerCount"] = 10;
    dev1["pollInterval"] = 1000;
    s_deviceList.append(dev1);

    QVariantMap dev2;
    dev2["id"] = s_nextDeviceId++;
    dev2["modbusAddress"] = 2;
    dev2["name"] = "压力表";
    dev2["type"] = "传感器";
    dev2["status"] = "在线";
    dev2["online"] = true;
    dev2["functionCode"] = 3;
    dev2["startAddress"] = 0;
    dev2["registerCount"] = 5;
    dev2["pollInterval"] = 2000;
    s_deviceList.append(dev2);

    QVariantMap dev3;
    dev3["id"] = s_nextDeviceId++;
    dev3["modbusAddress"] = 3;
    dev3["name"] = "流量计";
    dev3["type"] = "仪表";
    dev3["status"] = "离线";
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
    dev["status"] = "未知";
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
    return Result::error(404, "设备不存在");
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
    return Result::error(404, "设备不存在");
}

Result DeviceService::scanModbusDevices()
{
    // 模拟扫描 - 返回发现的设备地址列表
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
    return Result::error(404, "设备不存在");
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
        return Result::error(1, "Modbus地址必须在1-247之间");
    }
    if (cfg.functionCode < 1 || cfg.functionCode > 6) {
        return Result::error(2, "无效的功能码");
    }
    if (cfg.startAddress < 0 || cfg.startAddress > 65535) {
        return Result::error(3, "无效的起始地址");
    }
    if (cfg.registerCount < 1 || cfg.registerCount > 125) {
        return Result::error(4, "寄存器数量必须在1-125之间");
    }
    if (cfg.pollInterval < 100 || cfg.pollInterval > 60000) {
        return Result::error(5, "轮询间隔必须在100-60000毫秒之间");
    }
    return Result::success();
}
