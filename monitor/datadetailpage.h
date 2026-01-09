/**
 * @file datadetailpage.h
 * @brief 数据详情页面定义
 *
 * 本文件定义了数据详情页面，用于显示单个寄存器的详细信息，
 * 包括当前值、最大值、最小值、平均值以及趋势图占位。
 */

#ifndef DATADETAILPAGE_H
#define DATADETAILPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QTimer>

/**
 * @class DataDetailPage
 * @brief 数据详情页面类
 *
 * 显示参数详情和统计信息。
 */
class DataDetailPage : public QWidget
{
    Q_OBJECT

public:
    explicit DataDetailPage(QWidget *parent = nullptr);
    ~DataDetailPage();

    /**
     * @brief 加载指定寄存器的数据
     * @param deviceId 设备ID
     * @param addr 寄存器地址
     */
    void loadData(int deviceId, int addr);

signals:
    void goBack();  ///< 返回上一页

private slots:
    void onRefreshTimer();

private:
    void setupUI();
    void setupTitleBar();
    void setupContent();
    void updateData();

    int m_deviceId;         ///< 设备ID
    int m_registerAddr;     ///< 寄存器地址

    // 标题栏
    QWidget *m_titleBar;        ///< 标题栏容器
    QPushButton *m_backBtn;     ///< 返回按钮
    QLabel *m_titleLabel;       ///< 标题标签

    // 当前值显示
    QFrame *m_valueCard;            ///< 当前值卡片
    QLabel *m_currentValueLabel;    ///< 当前值标签
    QLabel *m_unitLabel;            ///< 单位标签
    QLabel *m_updateTimeLabel;      ///< 更新时间标签

    // 统计信息
    QFrame *m_statsCard;        ///< 统计卡片
    QLabel *m_minValueLabel;    ///< 最小值标签
    QLabel *m_maxValueLabel;    ///< 最大值标签
    QLabel *m_avgValueLabel;    ///< 平均值标签

    // 趋势图占位
    QFrame *m_chartPlaceholder; ///< 趋势图占位
    QLabel *m_chartLabel;       ///< 趋势图标签

    // 定时器
    QTimer *m_refreshTimer;     ///< 刷新定时器
};

#endif // DATADETAILPAGE_H
