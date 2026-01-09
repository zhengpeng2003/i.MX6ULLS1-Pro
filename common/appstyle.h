#ifndef APPSTYLE_H
#define APPSTYLE_H

#include <QString>
#include <QColor>

class AppStyle
{
public:
    // Colors - Industrial Dark Theme
    static const QColor BG_PRIMARY;      // #1a1a2e - Main background
    static const QColor BG_CARD;         // #16213e - Card background
    static const QColor BG_BORDER;       // #0f3460 - Border color
    static const QColor ACCENT;          // #e94560 - Accent/highlight
    static const QColor TEXT_PRIMARY;    // #ffffff - Primary text
    static const QColor TEXT_SECONDARY;  // #a0a0a0 - Secondary text
    static const QColor SUCCESS;         // #00ff88 - Success indicator
    static const QColor WARNING;         // #ffaa00 - Warning indicator
    static const QColor ERROR;           // #ff4444 - Error indicator

    // Font sizes
    static const int FONT_TITLE;         // 16pt
    static const int FONT_BODY;          // 12pt
    static const int FONT_SMALL;         // 10pt
    static const int FONT_BUTTON;        // 14pt

    // Dimensions
    static const int BTN_MIN_HEIGHT;     // 48px - Touch friendly
    static const int BTN_MIN_WIDTH;      // 80px
    static const int SPACING;            // 8px
    static const int MARGIN;             // 10px
    static const int BORDER_RADIUS;      // 6px
    static const int STATUS_BAR_HEIGHT;  // 28px

    // Screen dimensions
    static const int SCREEN_WIDTH;       // 480px
    static const int SCREEN_HEIGHT;      // 272px

    // Get global stylesheet
    static QString getStyleSheet();

    // Get button stylesheet
    static QString getButtonStyle(bool isPrimary = true);

    // Get card stylesheet
    static QString getCardStyle();

    // Get table stylesheet
    static QString getTableStyle();

    // Get input field stylesheet
    static QString getInputStyle();

    // Get status bar stylesheet
    static QString getStatusBarStyle();
};

#endif // APPSTYLE_H
