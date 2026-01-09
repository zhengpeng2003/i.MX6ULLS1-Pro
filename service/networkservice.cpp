#include "networkservice.h"

static NetworkConfig s_networkConfig;

Result NetworkService::getNetworkConfig()
{
    QVariantMap config;
    config["useDhcp"] = s_networkConfig.useDhcp;
    config["ipAddress"] = s_networkConfig.ipAddress;
    config["gateway"] = s_networkConfig.gateway;
    config["subnet"] = s_networkConfig.subnet;
    config["dns1"] = s_networkConfig.dns1;
    config["dns2"] = s_networkConfig.dns2;

    return Result::success(config);
}

Result NetworkService::setNetworkConfig(const NetworkConfig &cfg)
{
    s_networkConfig = cfg;
    return Result::success();
}

Result NetworkService::applyNetworkSettings()
{
    // TODO: Implement actual network configuration
    // This would typically involve system calls to configure the network interface
    return Result::success();
}
