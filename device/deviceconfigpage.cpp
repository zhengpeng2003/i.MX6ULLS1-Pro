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

    m_titleLabel = new QLabel("Device Config", m_titleBar);
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

    // Device name
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setStyleSheet(inputStyle);
    m_nameEdit->setPlaceholderText("Enter device name");
    QLabel *nameLabel = new QLabel("Name:");
    nameLabel->setStyleSheet(labelStyle);
    formLayout->addRow(nameLabel, m_nameEdit);

    // Device type
    m_typeCombo = new QComboBox(this);
    m_typeCombo->setStyleSheet(inputStyle);
    m_typeCombo->addItems(QStringList() << "Sensor" << "Meter" << "Controller" << "Other");
    QLabel *typeLabel = new QLabel("Type:");
    typeLabel->setStyleSheet(labelStyle);
    formLayout->addRow(typeLabel, m_typeCombo);

    // Modbus address
    m_addrSpin = new QSpinBox(this);
    m_addrSpin->setStyleSheet(inputStyle);
    m_addrSpin->setRange(1, 247);
    m_addrSpin->setValue(1);
    QLabel *addrLabel = new QLabel("Address:");
    addrLabel->setStyleSheet(labelStyle);
    formLayout->addRow(addrLabel, m_addrSpin);

    // Function code
    m_funcCombo = new QComboBox(this);
    m_funcCombo->setStyleSheet(inputStyle);
    m_funcCombo->addItem("03 - Read Holding Registers", 3);
    m_funcCombo->addItem("04 - Read Input Registers", 4);
    m_funcCombo->addItem("01 - Read Coils", 1);
    m_funcCombo->addItem("02 - Read Discrete Inputs", 2);
    QLabel *funcLabel = new QLabel("Function:");
    funcLabel->setStyleSheet(labelStyle);
    formLayout->addRow(funcLabel, m_funcCombo);

    // Start address
    m_startAddrSpin = new QSpinBox(this);
    m_startAddrSpin->setStyleSheet(inputStyle);
    m_startAddrSpin->setRange(0, 65535);
    m_startAddrSpin->setValue(0);
    QLabel *startLabel = new QLabel("Start Addr:");
    startLabel->setStyleSheet(labelStyle);
    formLayout->addRow(startLabel, m_startAddrSpin);

    // Register count
    m_regCountSpin = new QSpinBox(this);
    m_regCountSpin->setStyleSheet(inputStyle);
    m_regCountSpin->setRange(1, 125);
    m_regCountSpin->setValue(10);
    QLabel *regLabel = new QLabel("Reg Count:");
    regLabel->setStyleSheet(labelStyle);
    formLayout->addRow(regLabel, m_regCountSpin);

    // Poll interval
    m_pollIntervalSpin = new QSpinBox(this);
    m_pollIntervalSpin->setStyleSheet(inputStyle);
    m_pollIntervalSpin->setRange(100, 60000);
    m_pollIntervalSpin->setSingleStep(100);
    m_pollIntervalSpin->setValue(1000);
    m_pollIntervalSpin->setSuffix(" ms");
    QLabel *pollLabel = new QLabel("Poll Interval:");
    pollLabel->setStyleSheet(labelStyle);
    formLayout->addRow(pollLabel, m_pollIntervalSpin);

    // Remark
    m_remarkEdit = new QLineEdit(this);
    m_remarkEdit->setStyleSheet(inputStyle);
    m_remarkEdit->setPlaceholderText("Optional remark");
    QLabel *remarkLabel = new QLabel("Remark:");
    remarkLabel->setStyleSheet(labelStyle);
    formLayout->addRow(remarkLabel, m_remarkEdit);
}

void DeviceConfigPage::setupButtons()
{
    m_cancelBtn = new QPushButton("Cancel", this);
    m_cancelBtn->setStyleSheet(AppStyle::getButtonStyle(false));
    m_cancelBtn->setMinimumHeight(44);
    m_cancelBtn->setMinimumWidth(100);
    connect(m_cancelBtn, &QPushButton::clicked, this, &DeviceConfigPage::onCancelClicked);

    m_saveBtn = new QPushButton("Save", this);
    m_saveBtn->setStyleSheet(AppStyle::getButtonStyle(true));
    m_saveBtn->setMinimumHeight(44);
    m_saveBtn->setMinimumWidth(100);
    connect(m_saveBtn, &QPushButton::clicked, this, &DeviceConfigPage::onSaveClicked);
}

void DeviceConfigPage::loadDevice(int deviceId)
{
    m_deviceId = deviceId;

    if (deviceId < 0) {
        // New device
        m_titleLabel->setText("Add Device");
        clearForm();
        return;
    }

    m_titleLabel->setText("Edit Device");

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

    // Set function code
    int funcCode = config["functionCode"].toInt();
    for (int i = 0; i < m_funcCombo->count(); ++i) {
        if (m_funcCombo->itemData(i).toInt() == funcCode) {
            m_funcCombo->setCurrentIndex(i);
            break;
        }
    }

    // Set type
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
        Toast::showWarning(this, "Please enter device name");
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
        Toast::showSuccess(this, "Device saved");
        emit saved();
    } else {
        Toast::showError(this, result.message);
    }
}

void DeviceConfigPage::onCancelClicked()
{
    emit goBack();
}
