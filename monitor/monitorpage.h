/**
 * @file monitorpage.h
 * @brief 实时监控页面定义
 *
 * 本文件定义了实时监控页面，用于显示选定设备的实时数据，
 * 支持启动/停止轮询采集、显示通信状态等功能。
 */

#ifndef MONITORPAGE_H
#define MONITORPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTimer>

/**
 * @class MonitorPage
 * @brief 实时监控页面类
 *
 * 显示设备实时数据，支持轮询控制。
 */
class MonitorPage : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorPage(QWidget *parent = nullptr);
    ~MonitorPage();

signals:
    void goBack();                              ///< 返回上一页
    void viewDetail(int deviceId, int addr);    ///< 查看数据详情

private slots:
    void onDeviceChanged(int index);
    void onStartStopClicked();
    void onPollTimer();
    void onTableDoubleClicked(int row, int column);

private:
    void setupUI();
    void setupTitleBar();
    void setupControls();
    void setupTable();
    void loadDevices();
    void updateData();
    void setPollingState(bool polling);

    // 标题栏
    QWidget *m_titleBar;        ///< 标题栏容器
    QPushButton *m_backBtn;     ///< 返回按钮
    QLabel *m_titleLabel;       ///< 标题标签

    // 控制区
    QComboBox *m_deviceCombo;   ///< 设备选择下拉框
    QPushButton *m_startStopBtn;///< 启动/停止按钮
    QLabel *m_statusLed;        ///< 状态指示灯
    QLabel *m_statusLabel;      ///< 状态文字标签

    // 数据表格
    QTableWidget *m_table;      ///< 数据表格

    // 定时器和状态
    QTimer *m_pollTimer;        ///< 轮询定时器
    bool m_isPolling;           ///< 是否正在轮询
    int m_currentDeviceId;      ///< 当前选中的设备ID
};

#endif // MONITORPAGE_H
