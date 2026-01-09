/**
 * @file systemservice.h
 * @brief 系统服务定义
 *
 * 本文件定义了系统级别的服务接口，包括获取系统信息、通信状态、
 * 串口配置、日志管理等功能。
 */

#ifndef SYSTEMSERVICE_H
#define SYSTEMSERVICE_H

#include "../common/result.h"

/**
 * @struct SerialConfig
 * @brief 串口配置结构体
 */
struct SerialConfig {
    QString port;       ///< 串口名称（如COM1、/dev/ttyS1）
    int baudRate;       ///< 波特率
    int dataBits;       ///< 数据位
    int parity;         ///< 校验位：0=无校验，1=偶校验，2=奇校验
    int stopBits;       ///< 停止位

    SerialConfig()
        : port("COM1"), baudRate(9600), dataBits(8), parity(0), stopBits(1) {}
};

/**
 * @class SystemService
 * @brief 系统服务类
 *
 * 提供系统级别的服务接口，包括系统信息、通信状态、串口配置、日志管理等。
 */
class SystemService
{
public:
    /**
     * @brief 获取系统信息
     * @return Result 包含CPU使用率、内存使用率、运行时间、版本号等信息
     */
    static Result getSystemInfo();

    /**
     * @brief 获取通信状态
     * @return Result 包含网络状态、RS485状态、通信正常率等信息
     */
    static Result getCommStatus();

    /**
     * @brief 获取串口配置
     * @return Result 包含当前串口参数配置
     */
    static Result getSerialConfig();

    /**
     * @brief 设置串口配置
     * @param cfg 串口配置参数
     * @return Result 设置结果
     */
    static Result setSerialConfig(const SerialConfig &cfg);

    /**
     * @brief 重启通信服务
     * @return Result 重启结果
     */
    static Result restartCommService();

    /**
     * @brief 获取系统运行日志
     * @return Result 包含系统日志列表
     */
    static Result getSystemLog();

    /**
     * @brief 获取通信日志
     * @return Result 包含通信过程日志列表
     */
    static Result getCommLog();

    /**
     * @brief 导出日志到文件
     * @param type 日志类型（system/comm）
     * @return Result 包含导出文件路径
     */
    static Result exportLog(const QString &type);
};

#endif // SYSTEMSERVICE_H
