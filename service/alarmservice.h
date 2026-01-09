#ifndef ALARMSERVICE_H
#define ALARMSERVICE_H

#include "../common/result.h"

struct AlarmRules {
    int commTimeout;          // Communication timeout (ms)
    double highLimit;         // Upper limit
    double lowLimit;          // Lower limit
    int duration;             // Duration before alarm (seconds)
    bool enableCommAlarm;
    bool enableLimitAlarm;

    AlarmRules()
        : commTimeout(3000), highLimit(100.0), lowLimit(0.0),
          duration(5), enableCommAlarm(true), enableLimitAlarm(true) {}
};

class AlarmService
{
public:
    // Get list of all alarms
    static Result getAlarmList();

    // Acknowledge an alarm
    static Result ackAlarm(int alarmId);

    // Clear an alarm
    static Result clearAlarm(int alarmId);

    // Load alarm rules
    static Result loadAlarmRules();

    // Save alarm rules
    static Result saveAlarmRules(const AlarmRules &rules);
};

#endif // ALARMSERVICE_H
