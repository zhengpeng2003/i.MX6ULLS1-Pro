#ifndef MODBUSSERVICE_H
#define MODBUSSERVICE_H

#include "../common/result.h"

class ModbusService
{
public:
    // Start polling for a device
    static Result startPolling(int deviceId);

    // Stop polling for a device
    static Result stopPolling(int deviceId);

    // Read holding registers (function code 03)
    static Result readHoldingRegisters(int deviceId);

    // Read input registers (function code 04)
    static Result readInputRegisters(int deviceId);

    // Get real-time value for a specific register
    static Result getRealtimeValue(int deviceId, int addr);

    // Get historical data for a specific register
    static Result getHistoryData(int deviceId, int addr);

    // Check if device is currently being polled
    static bool isPolling(int deviceId);
};

#endif // MODBUSSERVICE_H
