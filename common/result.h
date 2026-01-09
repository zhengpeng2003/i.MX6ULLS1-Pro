/**
 * @file result.h
 * @brief 统一返回结构定义
 *
 * 本文件定义了系统中所有API的统一返回结构Result，
 * 包含状态码、消息和数据三个字段，用于规范化接口返回格式。
 */

#ifndef RESULT_H
#define RESULT_H

#include <QString>
#include <QVariant>

/**
 * @struct Result
 * @brief 统一返回结构体
 *
 * 所有API统一返回此结构，便于调用者统一处理返回结果。
 */
struct Result {
    int code;           ///< 状态码：0表示成功，非0表示错误
    QString message;    ///< 给人看的说明文字
    QVariant data;      ///< 真正返回的数据内容

    /**
     * @brief 默认构造函数，初始化为成功状态
     */
    Result() : code(0), message("成功") {}

    /**
     * @brief 带状态码和消息的构造函数
     * @param c 状态码
     * @param msg 消息文字
     */
    Result(int c, const QString& msg) : code(c), message(msg) {}

    /**
     * @brief 完整构造函数
     * @param c 状态码
     * @param msg 消息文字
     * @param d 返回数据
     */
    Result(int c, const QString& msg, const QVariant& d) : code(c), message(msg), data(d) {}

    /**
     * @brief 判断是否成功
     * @return true表示成功，false表示失败
     */
    bool isSuccess() const { return code == 0; }

    /**
     * @brief 判断是否失败
     * @return true表示失败，false表示成功
     */
    bool isError() const { return code != 0; }

    /**
     * @brief 快速创建成功结果
     * @param data 返回的数据（可选）
     * @return 成功的Result对象
     */
    static Result success(const QVariant& data = QVariant()) {
        return Result(0, "成功", data);
    }

    /**
     * @brief 快速创建错误结果
     * @param code 错误码
     * @param msg 错误消息
     * @return 错误的Result对象
     */
    static Result error(int code, const QString& msg) {
        return Result(code, msg);
    }
};

#endif // RESULT_H
