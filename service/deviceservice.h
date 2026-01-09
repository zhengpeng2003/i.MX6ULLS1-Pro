/**
 * @file deviceservice.h
 * @brief 设备服务定义
 *
 * 本文件定义了设备管理相关的服务接口，包括设备的增删改查、
 * 扫描Modbus设备、加载保存配置、配置校验等功能。
 */

#ifndef DEVICESERVICE_H
#define DEVICESERVICE_H

#include "../common/result.h"

/**
 * @struct DeviceConfig
 * @brief 设备配置结构体
 */
struct DeviceConfig {
    int id;                 ///< 设备ID（-1表示新设备）
    int modbusAddress;      ///< Modbus从站地址（1-247）
    int functionCode;       ///< 功能码（如03读保持寄存器、04读输入寄存器）
    int startAddress;       ///< 起始寄存器地址
    int registerCount;      ///< 寄存器数量
    int pollInterval;       ///< 轮询间隔（毫秒）
    QString name;           ///< 设备名称
    QString type;           ///< 设备类型
    QString remark;         ///< 备注信息
    bool enabled;           ///< 是否启用

    DeviceConfig()
        : id(-1), modbusAddress(1), functionCode(3), startAddress(0),
          registerCount(10), pollInterval(1000), enabled(true) {}
};

/**
 * @class DeviceService
 * @brief 设备服务类
 *
 * 提供设备管理的所有接口，包括列表查询、增删改查、扫描设备等。
 */
class DeviceService
{
public:
    /**
     * @brief 获取所有设备列表
     * @return Result 包含设备列表数据
     */
    static Result getDeviceList();

    /**
     * @brief 添加新设备
     * @param cfg 设备配置
     * @return Result 包含新设备ID
     */
    static Result addDevice(const DeviceConfig &cfg);

    /**
     * @brief 更新设备配置
     * @param id 设备ID
     * @param cfg 新的设备配置
     * @return Result 更新结果
     */
    static Result updateDevice(int id, const DeviceConfig &cfg);

    /**
     * @brief 删除设备
     * @param id 设备ID
     * @return Result 删除结果
     */
    static Result removeDevice(int id);

    /**
     * @brief 扫描RS485总线上的Modbus设备
     * @return Result 包含发现的设备地址列表
     */
    static Result scanModbusDevices();

    /**
     * @brief 加载指定设备的配置
     * @param id 设备ID
     * @return Result 包含设备配置数据
     */
    static Result loadDeviceConfig(int id);

    /**
     * @brief 保存设备配置（新增或更新）
     * @param id 设备ID（-1表示新增）
     * @param cfg 设备配置
     * @return Result 保存结果
     */
    static Result saveDeviceConfig(int id, const DeviceConfig &cfg);

    /**
     * @brief 校验设备配置是否有效
     * @param cfg 设备配置
     * @return Result 校验结果，失败时包含错误信息
     */
    static Result validateConfig(const DeviceConfig &cfg);
};

#endif // DEVICESERVICE_H
