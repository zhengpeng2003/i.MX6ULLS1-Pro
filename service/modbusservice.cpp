/**
 * @file modbusservice.cpp
 * @brief Modbus通信服务实现
 *
 * 本文件实现了Modbus通信服务的所有功能，包括轮询控制、
 * 寄存器读取等。当前为模拟数据，实际部署时需替换为真实Modbus通信。
 */

#include "modbusservice.h"
#include <QRandomGenerator>
#include <QDateTime>
#include <QSet>

// 正在轮询的设备ID集合
static QSet<int> s_pollingDevices;

Result ModbusService::startPolling(int deviceId)
{
    s_pollingDevices.insert(deviceId);
    return Result::success();
}

Result ModbusService::stopPolling(int deviceId)
{
    s_pollingDevices.remove(deviceId);
    return Result::success();
}

bool ModbusService::isPolling(int deviceId)
{
    return s_pollingDevices.contains(deviceId);
}

Result ModbusService::readHoldingRegisters(int deviceId)
{
    Q_UNUSED(deviceId)

    // 模拟寄存器数据
    QVariantList registers;
    for (int i = 0; i < 10; ++i) {
        QVariantMap reg;
        reg["address"] = i;
        reg["name"] = QString("寄存器 %1").arg(i);
        reg["value"] = QRandomGenerator::global()->bounded(0, 10000);
        reg["unit"] = (i % 2 == 0) ? "℃" : "bar";
        reg["updateTime"] = QDateTime::currentDateTime().toString("hh:mm:ss");
        registers.append(reg);
    }

    return Result::success(registers);
}

Result ModbusService::readInputRegisters(int deviceId)
{
    Q_UNUSED(deviceId)

    // 模拟输入寄存器数据
    QVariantList registers;
    for (int i = 0; i < 5; ++i) {
        QVariantMap reg;
        reg["address"] = 100 + i;
        reg["name"] = QString("输入 %1").arg(i);
        reg["value"] = QRandomGenerator::global()->bounded(0, 5000);
        reg["unit"] = "mA";
        reg["updateTime"] = QDateTime::currentDateTime().toString("hh:mm:ss");
        registers.append(reg);
    }

    return Result::success(registers);
}

Result ModbusService::getRealtimeValue(int deviceId, int addr)
{
    Q_UNUSED(deviceId)
    Q_UNUSED(addr)

    // 模拟实时值
    QVariantMap data;
    data["value"] = QRandomGenerator::global()->bounded(0, 10000) / 100.0;
    data["unit"] = "℃";
    data["updateTime"] = QDateTime::currentDateTime().toString("hh:mm:ss");
    data["quality"] = "良好";

    return Result::success(data);
}

Result ModbusService::getHistoryData(int deviceId, int addr)
{
    Q_UNUSED(deviceId)
    Q_UNUSED(addr)

    // 模拟历史数据
    QVariantMap data;
    data["currentValue"] = QRandomGenerator::global()->bounded(200, 300) / 10.0;
    data["minValue"] = 18.5;
    data["maxValue"] = 32.7;
    data["avgValue"] = 24.3;
    data["updateTime"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // 用于图表的历史数据点
    QVariantList history;
    double base = 25.0;
    for (int i = 0; i < 60; ++i) {
        QVariantMap point;
        point["time"] = QDateTime::currentDateTime().addSecs(-60 + i).toString("hh:mm");
        point["value"] = base + (QRandomGenerator::global()->bounded(-50, 50) / 10.0);
        history.append(point);
    }
    data["history"] = history;

    return Result::success(data);
}
