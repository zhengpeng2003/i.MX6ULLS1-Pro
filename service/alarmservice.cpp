/**
 * @file alarmservice.cpp
 * @brief 告警服务实现
 *
 * 本文件实现了告警管理服务的所有功能，包括告警列表查询、
 * 确认、清除、规则配置等。当前为模拟数据，实际部署时需替换为真实数据存储。
 */

#include "alarmservice.h"
#include <QDateTime>

// 静态模拟告警列表
static QVariantList s_alarmList;
static int s_nextAlarmId = 1;
static bool s_alarmInitialized = false;
static AlarmRules s_alarmRules;

/**
 * @brief 初始化模拟告警数据
 */
static void initAlarmMockData()
{
    if (s_alarmInitialized) return;
    s_alarmInitialized = true;

    // 添加模拟告警
    QVariantMap alarm1;
    alarm1["id"] = s_nextAlarmId++;
    alarm1["time"] = "2024-01-15 09:30:15";
    alarm1["device"] = "温度传感器";
    alarm1["type"] = "超上限";
    alarm1["level"] = "警告";
    alarm1["message"] = "温度超过35℃";
    alarm1["acknowledged"] = false;
    alarm1["status"] = "活动";
    s_alarmList.append(alarm1);

    QVariantMap alarm2;
    alarm2["id"] = s_nextAlarmId++;
    alarm2["time"] = "2024-01-15 08:45:22";
    alarm2["device"] = "流量计";
    alarm2["type"] = "通信失败";
    alarm2["level"] = "错误";
    alarm2["message"] = "设备无响应";
    alarm2["acknowledged"] = false;
    alarm2["status"] = "活动";
    s_alarmList.append(alarm2);

    QVariantMap alarm3;
    alarm3["id"] = s_nextAlarmId++;
    alarm3["time"] = "2024-01-15 07:20:00";
    alarm3["device"] = "压力表";
    alarm3["type"] = "低于下限";
    alarm3["level"] = "警告";
    alarm3["message"] = "压力低于1.0bar";
    alarm3["acknowledged"] = true;
    alarm3["status"] = "已确认";
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
            alarm["status"] = "已确认";
            alarm["ackTime"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            s_alarmList[i] = alarm;
            return Result::success();
        }
    }
    return Result::error(404, "告警不存在");
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
    return Result::error(404, "告警不存在");
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
