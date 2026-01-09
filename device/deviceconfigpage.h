/**
 * @file deviceconfigpage.h
 * @brief 设备配置页面定义
 *
 * 本文件定义了设备配置页面，用于添加新设备或编辑已有设备的配置参数，
 * 包括Modbus地址、功能码、寄存器设置等。
 */

#ifndef DEVICECONFIGPAGE_H
#define DEVICECONFIGPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>

/**
 * @class DeviceConfigPage
 * @brief 设备配置页面类
 *
 * 提供设备参数的配置表单界面。
 */
class DeviceConfigPage : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceConfigPage(QWidget *parent = nullptr);
    ~DeviceConfigPage();

    /**
     * @brief 加载设备配置
     * @param deviceId 设备ID，-1表示新增设备
     */
    void loadDevice(int deviceId);

signals:
    void goBack();  ///< 返回上一页
    void saved();   ///< 保存成功

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    void setupUI();
    void setupTitleBar();
    void setupForm();
    void setupButtons();
    void clearForm();
    bool validateInput();

    int m_deviceId;             ///< 当前设备ID

    // 标题栏
    QWidget *m_titleBar;        ///< 标题栏容器
    QPushButton *m_backBtn;     ///< 返回按钮
    QLabel *m_titleLabel;       ///< 标题标签

    // 表单控件
    QSpinBox *m_addrSpin;           ///< Modbus地址输入框
    QComboBox *m_funcCombo;         ///< 功能码选择框
    QSpinBox *m_startAddrSpin;      ///< 起始地址输入框
    QSpinBox *m_regCountSpin;       ///< 寄存器数量输入框
    QSpinBox *m_pollIntervalSpin;   ///< 轮询间隔输入框
    QLineEdit *m_nameEdit;          ///< 设备名称输入框
    QComboBox *m_typeCombo;         ///< 设备类型选择框
    QLineEdit *m_remarkEdit;        ///< 备注输入框

    // 按钮
    QPushButton *m_saveBtn;     ///< 保存按钮
    QPushButton *m_cancelBtn;   ///< 取消按钮
};

#endif // DEVICECONFIGPAGE_H
