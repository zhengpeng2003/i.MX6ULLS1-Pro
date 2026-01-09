#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include "../common/result.h"

struct NetworkConfig {
    bool useDhcp;
    QString ipAddress;
    QString gateway;
    QString subnet;
    QString dns1;
    QString dns2;

    NetworkConfig()
        : useDhcp(true), ipAddress("192.168.1.100"),
          gateway("192.168.1.1"), subnet("255.255.255.0"),
          dns1("8.8.8.8"), dns2("8.8.4.4") {}
};

class NetworkService
{
public:
    // Get current network configuration
    static Result getNetworkConfig();

    // Set network configuration
    static Result setNetworkConfig(const NetworkConfig &cfg);

    // Apply network settings (may require restart)
    static Result applyNetworkSettings();
};

#endif // NETWORKSERVICE_H
