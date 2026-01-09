/**
 * @file alarmservice.h
 * @brief 告警服务定义
 *
 * 本文件定义了告警管理相关的服务接口，包括告警列表查询、
 * 告警确认、告警清除、告警规则配置等功能。
 */

#ifndef ALARMSERVICE_H
#define ALARMSERVICE_H

#include "../common/result.h"

/**
 * @struct AlarmRules
 * @brief 告警规则结构体
 */
struct AlarmRules {
    int commTimeout;          ///< 通信超时时间（毫秒）
    double highLimit;         ///< 上限值
    double lowLimit;          ///< 下限值
    int duration;             ///< 持续时间后触发告警（秒）
    bool enableCommAlarm;     ///< 是否启用通信告警
    bool enableLimitAlarm;    ///< 是否启用限值告警

    AlarmRules()
        : commTimeout(3000), highLimit(100.0), lowLimit(0.0),
          duration(5), enableCommAlarm(true), enableLimitAlarm(true) {}
};

/**
 * @class AlarmService
 * @brief 告警服务类
 *
 * 提供告警管理的所有接口，包括列表查询、确认、清除、规则配置等。
 */
class AlarmService
{
public:
    /**
     * @brief 获取所有告警列表
     * @return Result 包含告警列表数据
     */
    static Result getAlarmList();

    /**
     * @brief 确认告警
     * @param alarmId 告警ID
     * @return Result 确认结果
     */
    static Result ackAlarm(int alarmId);

    /**
     * @brief 清除告警
     * @param alarmId 告警ID
     * @return Result 清除结果
     */
    static Result clearAlarm(int alarmId);

    /**
     * @brief 加载告警规则配置
     * @return Result 包含告警规则数据
     */
    static Result loadAlarmRules();

    /**
     * @brief 保存告警规则配置
     * @param rules 告警规则
     * @return Result 保存结果
     */
    static Result saveAlarmRules(const AlarmRules &rules);
};

#endif // ALARMSERVICE_H
