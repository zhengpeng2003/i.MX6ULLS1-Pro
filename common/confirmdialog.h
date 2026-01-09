/**
 * @file confirmdialog.h
 * @brief 确认对话框组件定义
 *
 * 本文件定义了确认对话框组件，用于在执行重要操作前让用户确认，
 * 适配触控操作，按钮尺寸较大，便于点击。
 */

#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

/**
 * @class ConfirmDialog
 * @brief 确认对话框类
 *
 * 用于显示确认对话框，包含标题、消息和确认/取消按钮。
 */
class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit ConfirmDialog(QWidget *parent = nullptr);
    ~ConfirmDialog();

    /**
     * @brief 设置对话框标题
     * @param title 标题文字
     */
    void setTitle(const QString &title);

    /**
     * @brief 设置对话框消息内容
     * @param message 消息文字
     */
    void setMessage(const QString &message);

    /**
     * @brief 设置确认按钮文字
     * @param text 按钮文字
     */
    void setConfirmText(const QString &text);

    /**
     * @brief 设置取消按钮文字
     * @param text 按钮文字
     */
    void setCancelText(const QString &text);

    /**
     * @brief 显示确认对话框（带标题）
     * @param parent 父窗口指针
     * @param title 对话框标题
     * @param message 消息内容
     * @return true表示用户点击确认，false表示用户点击取消
     */
    static bool confirm(QWidget *parent, const QString &title, const QString &message);

    /**
     * @brief 显示确认对话框（使用默认标题）
     * @param parent 父窗口指针
     * @param message 消息内容
     * @return true表示用户点击确认，false表示用户点击取消
     */
    static bool confirm(QWidget *parent, const QString &message);

private:
    void setupUI();

    QLabel *m_titleLabel;       ///< 标题标签
    QLabel *m_messageLabel;     ///< 消息标签
    QPushButton *m_confirmBtn;  ///< 确认按钮
    QPushButton *m_cancelBtn;   ///< 取消按钮
};

#endif // CONFIRMDIALOG_H
