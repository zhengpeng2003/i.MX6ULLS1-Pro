/**
 * @file networkpage.h
 * @brief 网络设置页面定义
 *
 * 本文件定义了网络设置页面，用于配置设备的网络参数，
 * 包括IP地址、子网掩码和网关设置。
 */

#ifndef NETWORKPAGE_H
#define NETWORKPAGE_H

#include <QWidget>

/**
 * @class NetworkPage
 * @brief 网络设置页面类
 *
 * 提供网络参数配置界面，支持静态IP配置。
 */
class NetworkPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit NetworkPage(QWidget *parent = nullptr);

signals:
    void goBack();  ///< 返回上一页信号
};

#endif // NETWORKPAGE_H
