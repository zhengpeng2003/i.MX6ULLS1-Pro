/**
 * @file networkservice.h
 * @brief 网络服务定义
 *
 * 本文件定义了网络配置相关的服务接口，包括获取网络配置、
 * 设置网络参数、应用网络设置等功能。
 */

#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include "../common/result.h"

/**
 * @struct NetworkConfig
 * @brief 网络配置结构体
 */
struct NetworkConfig {
    bool useDhcp;       ///< 是否使用DHCP自动获取IP
    QString ipAddress;  ///< IP地址
    QString gateway;    ///< 网关地址
    QString subnet;     ///< 子网掩码
    QString dns1;       ///< 首选DNS服务器
    QString dns2;       ///< 备用DNS服务器

    NetworkConfig()
        : useDhcp(true), ipAddress("192.168.1.100"),
          gateway("192.168.1.1"), subnet("255.255.255.0"),
          dns1("8.8.8.8"), dns2("8.8.4.4") {}
};

/**
 * @class NetworkService
 * @brief 网络服务类
 *
 * 提供网络配置管理的所有接口。
 */
class NetworkService
{
public:
    /**
     * @brief 获取当前网络配置
     * @return Result 包含网络配置数据
     */
    static Result getNetworkConfig();

    /**
     * @brief 设置网络配置
     * @param cfg 网络配置参数
     * @return Result 设置结果
     */
    static Result setNetworkConfig(const NetworkConfig &cfg);

    /**
     * @brief 应用网络设置（可能需要重启网络服务）
     * @return Result 应用结果
     */
    static Result applyNetworkSettings();
};

#endif // NETWORKSERVICE_H
