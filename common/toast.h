/**
 * @file toast.h
 * @brief 轻提示组件定义
 *
 * 本文件定义了Toast轻提示组件，用于在界面上显示短暂的提示信息，
 * 支持信息、成功、警告、错误四种类型，带淡入淡出动画效果。
 */

#ifndef TOAST_H
#define TOAST_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>

/**
 * @class Toast
 * @brief 轻提示组件类
 *
 * 用于显示短暂的提示信息，自动消失，适合触控操作反馈。
 */
class Toast : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    /**
     * @enum Type
     * @brief 提示类型枚举
     */
    enum Type {
        Info,       ///< 信息提示（蓝色）
        Success,    ///< 成功提示（绿色）
        Warning,    ///< 警告提示（橙色）
        Error       ///< 错误提示（红色）
    };

    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit Toast(QWidget *parent = nullptr);
    ~Toast();

    /**
     * @brief 显示提示信息（静态方法）
     * @param parent 父窗口指针
     * @param message 提示消息内容
     * @param type 提示类型，默认为Info
     * @param duration 显示时长（毫秒），默认2000ms
     */
    static void show(QWidget *parent, const QString &message, Type type = Info, int duration = 2000);

    /**
     * @brief 显示信息提示
     * @param parent 父窗口指针
     * @param message 提示消息内容
     * @param duration 显示时长（毫秒），默认2000ms
     */
    static void showInfo(QWidget *parent, const QString &message, int duration = 2000);

    /**
     * @brief 显示成功提示
     * @param parent 父窗口指针
     * @param message 提示消息内容
     * @param duration 显示时长（毫秒），默认2000ms
     */
    static void showSuccess(QWidget *parent, const QString &message, int duration = 2000);

    /**
     * @brief 显示警告提示
     * @param parent 父窗口指针
     * @param message 提示消息内容
     * @param duration 显示时长（毫秒），默认2000ms
     */
    static void showWarning(QWidget *parent, const QString &message, int duration = 2000);

    /**
     * @brief 显示错误提示
     * @param parent 父窗口指针
     * @param message 提示消息内容
     * @param duration 显示时长（毫秒），默认2000ms
     */
    static void showError(QWidget *parent, const QString &message, int duration = 2000);

    /**
     * @brief 获取当前透明度
     * @return 透明度值（0.0-1.0）
     */
    qreal opacity() const { return m_opacity; }

    /**
     * @brief 设置透明度
     * @param opacity 透明度值（0.0-1.0）
     */
    void setOpacity(qreal opacity);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void showToast(const QString &message, Type type, int duration);
    void fadeOut();

    QLabel *m_label;                    ///< 文字标签
    QTimer *m_timer;                    ///< 定时器
    QPropertyAnimation *m_animation;    ///< 动画对象
    qreal m_opacity;                    ///< 当前透明度
    Type m_type;                        ///< 提示类型
};

#endif // TOAST_H
