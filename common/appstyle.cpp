/**
 * @file appstyle.cpp
 * @brief 应用全局样式实现
 *
 * 本文件实现了全局样式的具体定义和各类样式表的生成方法。
 */

#include "appstyle.h"

// 颜色定义
const QColor AppStyle::BG_PRIMARY     = QColor("#1a1a2e");
const QColor AppStyle::BG_CARD        = QColor("#16213e");
const QColor AppStyle::BG_BORDER      = QColor("#0f3460");
const QColor AppStyle::ACCENT         = QColor("#e94560");
const QColor AppStyle::TEXT_PRIMARY   = QColor("#ffffff");
const QColor AppStyle::TEXT_SECONDARY = QColor("#a0a0a0");
const QColor AppStyle::SUCCESS        = QColor("#00ff88");
const QColor AppStyle::WARNING        = QColor("#ffaa00");
const QColor AppStyle::ERROR          = QColor("#ff4444");

// Font sizes
const int AppStyle::FONT_TITLE  = 16;
const int AppStyle::FONT_BODY   = 12;
const int AppStyle::FONT_SMALL  = 10;
const int AppStyle::FONT_BUTTON = 14;

// Dimensions
const int AppStyle::BTN_MIN_HEIGHT    = 48;
const int AppStyle::BTN_MIN_WIDTH     = 80;
const int AppStyle::SPACING           = 8;
const int AppStyle::MARGIN            = 10;
const int AppStyle::BORDER_RADIUS     = 6;
const int AppStyle::STATUS_BAR_HEIGHT = 28;

// Screen dimensions
const int AppStyle::SCREEN_WIDTH  = 480;
const int AppStyle::SCREEN_HEIGHT = 272;

QString AppStyle::getStyleSheet()
{
    return QString(
        "QWidget {"
        "   background-color: #1a1a2e;"
        "   color: #ffffff;"
        "   font-family: 'Microsoft YaHei', 'SimHei', sans-serif;"
        "   font-size: 12pt;"
        "}"
        "QLabel {"
        "   background-color: transparent;"
        "}"
        "QPushButton {"
        "   background-color: #0f3460;"
        "   color: #ffffff;"
        "   border: 1px solid #16213e;"
        "   border-radius: 6px;"
        "   padding: 8px 16px;"
        "   min-height: 40px;"
        "   font-size: 14pt;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #16213e;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #e94560;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #2a2a3e;"
        "   color: #606060;"
        "}"
        "QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox {"
        "   background-color: #16213e;"
        "   color: #ffffff;"
        "   border: 1px solid #0f3460;"
        "   border-radius: 4px;"
        "   padding: 6px;"
        "   min-height: 32px;"
        "}"
        "QLineEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {"
        "   border: 1px solid #e94560;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "   width: 30px;"
        "}"
        "QComboBox::down-arrow {"
        "   image: none;"
        "   border-left: 5px solid transparent;"
        "   border-right: 5px solid transparent;"
        "   border-top: 8px solid #ffffff;"
        "   margin-right: 10px;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #16213e;"
        "   color: #ffffff;"
        "   selection-background-color: #e94560;"
        "}"
        "QTableWidget {"
        "   background-color: #16213e;"
        "   color: #ffffff;"
        "   border: 1px solid #0f3460;"
        "   gridline-color: #0f3460;"
        "   selection-background-color: #e94560;"
        "}"
        "QTableWidget::item {"
        "   padding: 8px;"
        "}"
        "QHeaderView::section {"
        "   background-color: #0f3460;"
        "   color: #ffffff;"
        "   padding: 8px;"
        "   border: none;"
        "   font-weight: bold;"
        "}"
        "QScrollBar:vertical {"
        "   background-color: #1a1a2e;"
        "   width: 16px;"
        "   border-radius: 8px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background-color: #0f3460;"
        "   min-height: 40px;"
        "   border-radius: 8px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   height: 0px;"
        "}"
        "QScrollBar:horizontal {"
        "   background-color: #1a1a2e;"
        "   height: 16px;"
        "   border-radius: 8px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "   background-color: #0f3460;"
        "   min-width: 40px;"
        "   border-radius: 8px;"
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "   width: 0px;"
        "}"
        "QTextEdit {"
        "   background-color: #16213e;"
        "   color: #ffffff;"
        "   border: 1px solid #0f3460;"
        "   border-radius: 4px;"
        "}"
        "QProgressBar {"
        "   background-color: #16213e;"
        "   border: 1px solid #0f3460;"
        "   border-radius: 4px;"
        "   text-align: center;"
        "   color: #ffffff;"
        "}"
        "QProgressBar::chunk {"
        "   background-color: #e94560;"
        "   border-radius: 3px;"
        "}"
        "QTabWidget::pane {"
        "   background-color: #16213e;"
        "   border: 1px solid #0f3460;"
        "}"
        "QTabBar::tab {"
        "   background-color: #0f3460;"
        "   color: #ffffff;"
        "   padding: 10px 20px;"
        "   border-top-left-radius: 4px;"
        "   border-top-right-radius: 4px;"
        "}"
        "QTabBar::tab:selected {"
        "   background-color: #e94560;"
        "}"
        "QRadioButton, QCheckBox {"
        "   color: #ffffff;"
        "   spacing: 8px;"
        "}"
        "QRadioButton::indicator, QCheckBox::indicator {"
        "   width: 20px;"
        "   height: 20px;"
        "}"
    );
}

QString AppStyle::getButtonStyle(bool isPrimary)
{
    if (isPrimary) {
        return QString(
            "QPushButton {"
            "   background-color: #e94560;"
            "   color: #ffffff;"
            "   border: none;"
            "   border-radius: 6px;"
            "   padding: 10px 20px;"
            "   min-height: 40px;"
            "   font-size: 14pt;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background-color: #ff6b8a;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #c73e55;"
            "}"
        );
    } else {
        return QString(
            "QPushButton {"
            "   background-color: #0f3460;"
            "   color: #ffffff;"
            "   border: 1px solid #16213e;"
            "   border-radius: 6px;"
            "   padding: 10px 20px;"
            "   min-height: 40px;"
            "   font-size: 14pt;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background-color: #16213e;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #e94560;"
            "}"
        );
    }
}

QString AppStyle::getCardStyle()
{
    return QString(
        "QFrame {"
        "   background-color: #16213e;"
        "   border: 1px solid #0f3460;"
        "   border-radius: 8px;"
        "}"
    );
}

QString AppStyle::getTableStyle()
{
    return QString(
        "QTableWidget {"
        "   background-color: #16213e;"
        "   color: #ffffff;"
        "   border: 1px solid #0f3460;"
        "   border-radius: 4px;"
        "   gridline-color: #0f3460;"
        "   selection-background-color: #e94560;"
        "}"
        "QTableWidget::item {"
        "   padding: 6px;"
        "   border-bottom: 1px solid #0f3460;"
        "}"
        "QTableWidget::item:selected {"
        "   background-color: #e94560;"
        "}"
        "QHeaderView::section {"
        "   background-color: #0f3460;"
        "   color: #ffffff;"
        "   padding: 8px;"
        "   border: none;"
        "   font-weight: bold;"
        "}"
    );
}

QString AppStyle::getInputStyle()
{
    return QString(
        "QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox {"
        "   background-color: #16213e;"
        "   color: #ffffff;"
        "   border: 1px solid #0f3460;"
        "   border-radius: 4px;"
        "   padding: 8px;"
        "   min-height: 36px;"
        "   font-size: 12pt;"
        "}"
        "QLineEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {"
        "   border: 2px solid #e94560;"
        "}"
    );
}

QString AppStyle::getStatusBarStyle()
{
    return QString(
        "QFrame {"
        "   background-color: #0f3460;"
        "   border: none;"
        "   border-radius: 0px;"
        "}"
        "QLabel {"
        "   color: #ffffff;"
        "   font-size: 10pt;"
        "   background-color: transparent;"
        "}"
    );
}
