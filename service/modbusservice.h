/**
 * @file modbusservice.h
 * @brief Modbus通信服务定义
 *
 * 本文件定义了Modbus通信相关的服务接口，包括轮询控制、
 * 读取保持寄存器、读取输入寄存器、获取实时值和历史数据等功能。
 */

#ifndef MODBUSSERVICE_H
#define MODBUSSERVICE_H

#include "../common/result.h"

/**
 * @class ModbusService
 * @brief Modbus通信服务类
 *
 * 提供Modbus协议通信的所有接口，包括轮询控制和寄存器读写。
 */
class ModbusService
{
public:
    /**
     * @brief 开始轮询指定设备
     * @param deviceId 设备ID
     * @return Result 操作结果
     */
    static Result startPolling(int deviceId);

    /**
     * @brief 停止轮询指定设备
     * @param deviceId 设备ID
     * @return Result 操作结果
     */
    static Result stopPolling(int deviceId);

    /**
     * @brief 读取保持寄存器（功能码03）
     * @param deviceId 设备ID
     * @return Result 包含寄存器数据列表
     */
    static Result readHoldingRegisters(int deviceId);

    /**
     * @brief 读取输入寄存器（功能码04）
     * @param deviceId 设备ID
     * @return Result 包含寄存器数据列表
     */
    static Result readInputRegisters(int deviceId);

    /**
     * @brief 获取指定寄存器的实时值
     * @param deviceId 设备ID
     * @param addr 寄存器地址
     * @return Result 包含实时值、单位、更新时间等信息
     */
    static Result getRealtimeValue(int deviceId, int addr);

    /**
     * @brief 获取指定寄存器的历史数据
     * @param deviceId 设备ID
     * @param addr 寄存器地址
     * @return Result 包含历史数据用于趋势分析
     */
    static Result getHistoryData(int deviceId, int addr);

    /**
     * @brief 检查设备是否正在轮询
     * @param deviceId 设备ID
     * @return true表示正在轮询，false表示未轮询
     */
    static bool isPolling(int deviceId);
};

#endif // MODBUSSERVICE_H
