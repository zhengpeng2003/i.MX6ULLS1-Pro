#ifndef SYSTEMSERVICE_H
#define SYSTEMSERVICE_H

#include "../common/result.h"

struct SerialConfig {
    QString port;
    int baudRate;
    int dataBits;
    int parity;      // 0=None, 1=Even, 2=Odd
    int stopBits;

    SerialConfig()
        : port("COM1"), baudRate(9600), dataBits(8), parity(0), stopBits(1) {}
};

class SystemService
{
public:
    // Get system information (CPU, memory usage)
    static Result getSystemInfo();

    // Get communication status (network, RS485, comm rate)
    static Result getCommStatus();

    // Get serial port configuration
    static Result getSerialConfig();

    // Set serial port configuration
    static Result setSerialConfig(const SerialConfig &cfg);

    // Restart communication service
    static Result restartCommService();

    // Get system log
    static Result getSystemLog();

    // Get communication log
    static Result getCommLog();

    // Export log to file
    static Result exportLog(const QString &type);
};

#endif // SYSTEMSERVICE_H
