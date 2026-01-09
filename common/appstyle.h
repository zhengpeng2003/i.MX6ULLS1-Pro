/**
 * @file appstyle.h
 * @brief 应用全局样式定义
 *
 * 本文件定义了整个应用的全局样式，包括颜色、字体大小、尺寸等，
 * 采用工业深色主题，高对比度设计，适配480×272触控屏。
 */

#ifndef APPSTYLE_H
#define APPSTYLE_H

#include <QString>
#include <QColor>

/**
 * @class AppStyle
 * @brief 应用样式类
 *
 * 提供全局统一的样式定义和样式表生成方法。
 */
class AppStyle
{
public:
    // ==================== 颜色定义 - 工业深色主题 ====================
    static const QColor BG_PRIMARY;      ///< #1a1a2e - 主背景色
    static const QColor BG_CARD;         ///< #16213e - 卡片背景色
    static const QColor BG_BORDER;       ///< #0f3460 - 边框颜色
    static const QColor ACCENT;          ///< #e94560 - 强调色/高亮色
    static const QColor TEXT_PRIMARY;    ///< #ffffff - 主要文字颜色
    static const QColor TEXT_SECONDARY;  ///< #a0a0a0 - 次要文字颜色
    static const QColor SUCCESS;         ///< #00ff88 - 成功状态颜色
    static const QColor WARNING;         ///< #ffaa00 - 警告状态颜色
    static const QColor ERROR;           ///< #ff4444 - 错误状态颜色

    // ==================== 字体大小 ====================
    static const int FONT_TITLE;         ///< 16pt - 标题字号
    static const int FONT_BODY;          ///< 12pt - 正文字号
    static const int FONT_SMALL;         ///< 10pt - 小字号
    static const int FONT_BUTTON;        ///< 14pt - 按钮字号

    // ==================== 尺寸定义 ====================
    static const int BTN_MIN_HEIGHT;     ///< 48px - 按钮最小高度（触控友好）
    static const int BTN_MIN_WIDTH;      ///< 80px - 按钮最小宽度
    static const int SPACING;            ///< 8px - 间距
    static const int MARGIN;             ///< 10px - 边距
    static const int BORDER_RADIUS;      ///< 6px - 圆角半径
    static const int STATUS_BAR_HEIGHT;  ///< 28px - 状态栏高度

    // ==================== 屏幕尺寸 ====================
    static const int SCREEN_WIDTH;       ///< 480px - 屏幕宽度
    static const int SCREEN_HEIGHT;      ///< 272px - 屏幕高度

    /**
     * @brief 获取全局样式表
     * @return 全局QSS样式字符串
     */
    static QString getStyleSheet();

    /**
     * @brief 获取按钮样式表
     * @param isPrimary true为主要按钮（强调色），false为次要按钮
     * @return 按钮QSS样式字符串
     */
    static QString getButtonStyle(bool isPrimary = true);

    /**
     * @brief 获取卡片样式表
     * @return 卡片QSS样式字符串
     */
    static QString getCardStyle();

    /**
     * @brief 获取表格样式表
     * @return 表格QSS样式字符串
     */
    static QString getTableStyle();

    /**
     * @brief 获取输入框样式表
     * @return 输入框QSS样式字符串
     */
    static QString getInputStyle();

    /**
     * @brief 获取状态栏样式表
     * @return 状态栏QSS样式字符串
     */
    static QString getStatusBarStyle();
};

#endif // APPSTYLE_H
