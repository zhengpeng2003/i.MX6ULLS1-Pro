/**
 * @file devicelistpage.h
 * @brief 设备列表页面定义
 *
 * 本文件定义了设备管理的列表页面，显示所有已配置设备的信息，
 * 支持添加、编辑、删除设备以及扫描RS485总线上的Modbus设备。
 */

#ifndef DEVICELISTPAGE_H
#define DEVICELISTPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

/**
 * @class DeviceListPage
 * @brief 设备列表页面类
 *
 * 显示设备列表，提供设备管理功能。
 */
class DeviceListPage : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceListPage(QWidget *parent = nullptr);
    ~DeviceListPage();

    /**
     * @brief 刷新设备列表
     */
    void refreshList();

signals:
    void goBack();                  ///< 返回上一页
    void addDevice();               ///< 添加新设备
    void editDevice(int deviceId);  ///< 编辑指定设备

private slots:
    void onAddClicked();
    void onEditClicked();
    void onDeleteClicked();
    void onScanClicked();
    void onTableSelectionChanged();

private:
    void setupUI();
    void setupTitleBar();
    void setupTable();
    void setupButtons();
    void loadDevices();
    int getSelectedDeviceId() const;

    // 标题栏
    QWidget *m_titleBar;        ///< 标题栏容器
    QPushButton *m_backBtn;     ///< 返回按钮
    QLabel *m_titleLabel;       ///< 标题标签

    // 表格
    QTableWidget *m_table;      ///< 设备表格

    // 扫描进度条
    QProgressBar *m_scanProgress;   ///< 扫描进度条

    // 按钮栏
    QWidget *m_buttonBar;       ///< 按钮栏容器
    QPushButton *m_addBtn;      ///< 添加按钮
    QPushButton *m_editBtn;     ///< 编辑按钮
    QPushButton *m_deleteBtn;   ///< 删除按钮
    QPushButton *m_scanBtn;     ///< 扫描按钮
};

#endif // DEVICELISTPAGE_H
