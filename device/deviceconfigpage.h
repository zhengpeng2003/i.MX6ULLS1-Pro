#ifndef DEVICECONFIGPAGE_H
#define DEVICECONFIGPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>

class DeviceConfigPage : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceConfigPage(QWidget *parent = nullptr);
    ~DeviceConfigPage();

    void loadDevice(int deviceId);

signals:
    void goBack();
    void saved();

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

    int m_deviceId;

    // Title bar
    QWidget *m_titleBar;
    QPushButton *m_backBtn;
    QLabel *m_titleLabel;

    // Form fields
    QSpinBox *m_addrSpin;
    QComboBox *m_funcCombo;
    QSpinBox *m_startAddrSpin;
    QSpinBox *m_regCountSpin;
    QSpinBox *m_pollIntervalSpin;
    QLineEdit *m_nameEdit;
    QComboBox *m_typeCombo;
    QLineEdit *m_remarkEdit;

    // Buttons
    QPushButton *m_saveBtn;
    QPushButton *m_cancelBtn;
};

#endif // DEVICECONFIGPAGE_H
