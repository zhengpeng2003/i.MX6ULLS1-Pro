/**
 * @file deviceconfigpage.cpp
 * @brief 设备配置页面实现
 *
 * 本文件实现了设备配置页面的所有功能，包括表单创建、数据加载、
 * 输入校验和保存操作。
 */

#include "deviceconfigpage.h"
#include "../common/appstyle.h"
#include "../common/toast.h"
#include "../service/deviceservice.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QScrollArea>

DeviceConfigPage::DeviceConfigPage(QWidget *parent)
    : QWidget(parent)
    , m_deviceId(-1)
    , m_titleBar(nullptr)
    , m_backBtn(nullptr)
    , m_titleLabel(nullptr)
    , m_addrSpin(nullptr)
    , m_funcCombo(nullptr)
    , m_startAddrSpin(nullptr)
    , m_regCountSpin(nullptr)
    , m_pollIntervalSpin(nullptr)
    , m_nameEdit(nullptr)
    , m_typeCombo(nullptr)
    , m_remarkEdit(nullptr)
    , m_saveBtn(nullptr)
    , m_cancelBtn(nullptr)
{
    setupUI();
}

DeviceConfigPage::~DeviceConfigPage()
{
}

void DeviceConfigPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    setupTitleBar();
    mainLayout->addWidget(m_titleBar);

    // Scrollable content area
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; background-color: transparent; }");

    QWidget *content = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(10, 8, 10, 8);
    contentLayout->setSpacing(8);

    setupForm();
    contentLayout->addLayout(static_cast<QFormLayout*>(m_addrSpin->parentWidget()->layout()));

    contentLayout->addStretch();

    setupButtons();
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);
    btnLayout->addWidget(m_cancelBtn);
    btnLayout->addWidget(m_saveBtn);
    contentLayout->addLayout(btnLayout);

    scrollArea->setWidget(content);
    mainLayout->addWidget(scrollArea, 1);
}

void DeviceConfigPage::setupTitleBar()
{
    m_titleBar = new QWidget(this);
    m_titleBar->setFixedHeight(40);
    m_titleBar->setStyleSheet("background-color: #0f3460;");

    QHBoxLayout *layout = new QHBoxLayout(m_titleBar);
    layout->setContentsMargins(5, 0, 10, 0);
    layout->setSpacing(10);

    m_backBtn = new QPushButton("<", m_titleBar);
    m_backBtn->setFixedSize(40, 36);
    m_backBtn->setStyleSheet(
        "QPushButton { background-color: transparent; color: #ffffff; font-size: 18pt; border: none; }"
        "QPushButton:pressed { background-color: #e94560; }"
    );
    connect(m_backBtn, &QPushButton::clicked, this, &DeviceConfigPage::goBack);
    layout->addWidget(m_backBtn);

    m_titleLabel = new QLabel("设备配置", m_titleBar);
    m_titleLabel->setStyleSheet("color: #ffffff; font-size: 16pt; font-weight: bold;");
    layout->addWidget(m_titleLabel);

    layout->addStretch();
}

void DeviceConfigPage::setupForm()
{
    QWidget *formWidget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->setSpacing(10);
    formLayout->setLabelAlignment(Qt::AlignRight);

    QString labelStyle = "color: #a0a0a0; font-size: 11pt;";
    QString inputStyle = AppStyle::getInputStyle();

    // 设备名称
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setStyleSheet(inputStyle);
    m_nameEdit->setPlaceholderText("请输入设备名称");
    QLabel *nameLabel = new QLabel("名称:");
    nameLabel->setStyleSheet(labelStyle);
    formLayout->addRow(nameLabel, m_nameEdit);

    // 设备类型
    m_typeCombo = new QComboBox(this);
    m_typeCombo->setStyleSheet(inputStyle);
    m_typeCombo->addItems(QStringList() << "传感器" << "仪表" << "控制器" << "其他");
    QLabel *typeLabel = new QLabel("类型:");
    typeLabel->setStyleSheet(labelStyle);
    formLayout->addRow(typeLabel, m_typeCombo);

    // Modbus地址
    m_addrSpin = new QSpinBox(this);
    m_addrSpin->setStyleSheet(inputStyle);
    m_addrSpin->setRange(1, 247);
    m_addrSpin->setValue(1);
    QLabel *addrLabel = new QLabel("地址:");
    addrLabel->setStyleSheet(labelStyle);
    formLayout->addRow(addrLabel, m_addrSpin);

    // 功能码
    m_funcCombo = new QComboBox(this);
    m_funcCombo->setStyleSheet(inputStyle);
    m_funcCombo->addItem("03 - 读保持寄存器", 3);
    m_funcCombo->addItem("04 - 读输入寄存器", 4);
    m_funcCombo->addItem("01 - 读线圈", 1);
    m_funcCombo->addItem("02 - 读离散输入", 2);
    QLabel *funcLabel = new QLabel("功能码:");
    funcLabel->setStyleSheet(labelStyle);
    formLayout->addRow(funcLabel, m_funcCombo);

    // 起始地址
    m_startAddrSpin = new QSpinBox(this);
    m_startAddrSpin->setStyleSheet(inputStyle);
    m_startAddrSpin->setRange(0, 65535);
    m_startAddrSpin->setValue(0);
    QLabel *startLabel = new QLabel("起始地址:");
    startLabel->setStyleSheet(labelStyle);
    formLayout->addRow(startLabel, m_startAddrSpin);

    // 寄存器数量
    m_regCountSpin = new QSpinBox(this);
    m_regCountSpin->setStyleSheet(inputStyle);
    m_regCountSpin->setRange(1, 125);
    m_regCountSpin->setValue(10);
    QLabel *regLabel = new QLabel("寄存器数:");
    regLabel->setStyleSheet(labelStyle);
    formLayout->addRow(regLabel, m_regCountSpin);

    // 轮询间隔
    m_pollIntervalSpin = new QSpinBox(this);
    m_pollIntervalSpin->setStyleSheet(inputStyle);
    m_pollIntervalSpin->setRange(100, 60000);
    m_pollIntervalSpin->setSingleStep(100);
    m_pollIntervalSpin->setValue(1000);
    m_pollIntervalSpin->setSuffix(" 毫秒");
    QLabel *pollLabel = new QLabel("轮询间隔:");
    pollLabel->setStyleSheet(labelStyle);
    formLayout->addRow(pollLabel, m_pollIntervalSpin);

    // 备注
    m_remarkEdit = new QLineEdit(this);
    m_remarkEdit->setStyleSheet(inputStyle);
    m_remarkEdit->setPlaceholderText("可选备注信息");
    QLabel *remarkLabel = new QLabel("备注:");
    remarkLabel->setStyleSheet(labelStyle);
    formLayout->addRow(remarkLabel, m_remarkEdit);
}

void DeviceConfigPage::setupButtons()
{
    m_cancelBtn = new QPushButton("取消", this);
    m_cancelBtn->setStyleSheet(AppStyle::getButtonStyle(false));
    m_cancelBtn->setMinimumHeight(44);
    m_cancelBtn->setMinimumWidth(100);
    connect(m_cancelBtn, &QPushButton::clicked, this, &DeviceConfigPage::onCancelClicked);

    m_saveBtn = new QPushButton("保存", this);
    m_saveBtn->setStyleSheet(AppStyle::getButtonStyle(true));
    m_saveBtn->setMinimumHeight(44);
    m_saveBtn->setMinimumWidth(100);
    connect(m_saveBtn, &QPushButton::clicked, this, &DeviceConfigPage::onSaveClicked);
}

void DeviceConfigPage::loadDevice(int deviceId)
{
    m_deviceId = deviceId;

    if (deviceId < 0) {
        // 新增设备
        m_titleLabel->setText("添加设备");
        clearForm();
        return;
    }

    m_titleLabel->setText("编辑设备");

    Result result = DeviceService::loadDeviceConfig(deviceId);
    if (!result.isSuccess()) {
        Toast::showError(this, result.message);
        return;
    }

    QVariantMap config = result.data.toMap();
    m_nameEdit->setText(config["name"].toString());
    m_addrSpin->setValue(config["modbusAddress"].toInt());
    m_startAddrSpin->setValue(config["startAddress"].toInt());
    m_regCountSpin->setValue(config["registerCount"].toInt());
    m_pollIntervalSpin->setValue(config["pollInterval"].toInt());
    m_remarkEdit->setText(config["remark"].toString());

    // 设置功能码
    int funcCode = config["functionCode"].toInt();
    for (int i = 0; i < m_funcCombo->count(); ++i) {
        if (m_funcCombo->itemData(i).toInt() == funcCode) {
            m_funcCombo->setCurrentIndex(i);
            break;
        }
    }

    // 设置类型
    QString type = config["type"].toString();
    int typeIndex = m_typeCombo->findText(type);
    if (typeIndex >= 0) {
        m_typeCombo->setCurrentIndex(typeIndex);
    }
}

void DeviceConfigPage::clearForm()
{
    m_nameEdit->clear();
    m_typeCombo->setCurrentIndex(0);
    m_addrSpin->setValue(1);
    m_funcCombo->setCurrentIndex(0);
    m_startAddrSpin->setValue(0);
    m_regCountSpin->setValue(10);
    m_pollIntervalSpin->setValue(1000);
    m_remarkEdit->clear();
}

bool DeviceConfigPage::validateInput()
{
    if (m_nameEdit->text().trimmed().isEmpty()) {
        Toast::showWarning(this, "请输入设备名称");
        m_nameEdit->setFocus();
        return false;
    }

    DeviceConfig cfg;
    cfg.modbusAddress = m_addrSpin->value();
    cfg.functionCode = m_funcCombo->currentData().toInt();
    cfg.startAddress = m_startAddrSpin->value();
    cfg.registerCount = m_regCountSpin->value();
    cfg.pollInterval = m_pollIntervalSpin->value();

    Result result = DeviceService::validateConfig(cfg);
    if (!result.isSuccess()) {
        Toast::showWarning(this, result.message);
        return false;
    }

    return true;
}

void DeviceConfigPage::onSaveClicked()
{
    if (!validateInput()) {
        return;
    }

    DeviceConfig cfg;
    cfg.id = m_deviceId;
    cfg.name = m_nameEdit->text().trimmed();
    cfg.type = m_typeCombo->currentText();
    cfg.modbusAddress = m_addrSpin->value();
    cfg.functionCode = m_funcCombo->currentData().toInt();
    cfg.startAddress = m_startAddrSpin->value();
    cfg.registerCount = m_regCountSpin->value();
    cfg.pollInterval = m_pollIntervalSpin->value();
    cfg.remark = m_remarkEdit->text();

    Result result = DeviceService::saveDeviceConfig(m_deviceId, cfg);
    if (result.isSuccess()) {
        Toast::showSuccess(this, "设备已保存");
        emit saved();
    } else {
        Toast::showError(this, result.message);
    }
}

void DeviceConfigPage::onCancelClicked()
{
    emit goBack();
}
