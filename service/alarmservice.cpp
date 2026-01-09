#include "alarmservice.h"
#include <QDateTime>

// Static mock alarm list
static QVariantList s_alarmList;
static int s_nextAlarmId = 1;
static bool s_alarmInitialized = false;
static AlarmRules s_alarmRules;

static void initAlarmMockData()
{
    if (s_alarmInitialized) return;
    s_alarmInitialized = true;

    // Add some mock alarms
    QVariantMap alarm1;
    alarm1["id"] = s_nextAlarmId++;
    alarm1["time"] = "2024-01-15 09:30:15";
    alarm1["device"] = "Temperature Sensor";
    alarm1["type"] = "High Limit";
    alarm1["level"] = "Warning";
    alarm1["message"] = "Temperature exceeds 35C";
    alarm1["acknowledged"] = false;
    alarm1["status"] = "Active";
    s_alarmList.append(alarm1);

    QVariantMap alarm2;
    alarm2["id"] = s_nextAlarmId++;
    alarm2["time"] = "2024-01-15 08:45:22";
    alarm2["device"] = "Flow Meter";
    alarm2["type"] = "Comm Fail";
    alarm2["level"] = "Error";
    alarm2["message"] = "No response from device";
    alarm2["acknowledged"] = false;
    alarm2["status"] = "Active";
    s_alarmList.append(alarm2);

    QVariantMap alarm3;
    alarm3["id"] = s_nextAlarmId++;
    alarm3["time"] = "2024-01-15 07:20:00";
    alarm3["device"] = "Pressure Gauge";
    alarm3["type"] = "Low Limit";
    alarm3["level"] = "Warning";
    alarm3["message"] = "Pressure below 1.0 bar";
    alarm3["acknowledged"] = true;
    alarm3["status"] = "Acknowledged";
    s_alarmList.append(alarm3);
}

Result AlarmService::getAlarmList()
{
    initAlarmMockData();
    return Result::success(s_alarmList);
}

Result AlarmService::ackAlarm(int alarmId)
{
    initAlarmMockData();

    for (int i = 0; i < s_alarmList.size(); ++i) {
        QVariantMap alarm = s_alarmList[i].toMap();
        if (alarm["id"].toInt() == alarmId) {
            alarm["acknowledged"] = true;
            alarm["status"] = "Acknowledged";
            alarm["ackTime"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            s_alarmList[i] = alarm;
            return Result::success();
        }
    }
    return Result::error(404, "Alarm not found");
}

Result AlarmService::clearAlarm(int alarmId)
{
    initAlarmMockData();

    for (int i = 0; i < s_alarmList.size(); ++i) {
        if (s_alarmList[i].toMap()["id"].toInt() == alarmId) {
            s_alarmList.removeAt(i);
            return Result::success();
        }
    }
    return Result::error(404, "Alarm not found");
}

Result AlarmService::loadAlarmRules()
{
    QVariantMap rules;
    rules["commTimeout"] = s_alarmRules.commTimeout;
    rules["highLimit"] = s_alarmRules.highLimit;
    rules["lowLimit"] = s_alarmRules.lowLimit;
    rules["duration"] = s_alarmRules.duration;
    rules["enableCommAlarm"] = s_alarmRules.enableCommAlarm;
    rules["enableLimitAlarm"] = s_alarmRules.enableLimitAlarm;

    return Result::success(rules);
}

Result AlarmService::saveAlarmRules(const AlarmRules &rules)
{
    s_alarmRules = rules;
    return Result::success();
}
