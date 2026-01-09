#ifndef DEVICELISTPAGE_H
#define DEVICELISTPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

class DeviceListPage : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceListPage(QWidget *parent = nullptr);
    ~DeviceListPage();

    void refreshList();

signals:
    void goBack();
    void addDevice();
    void editDevice(int deviceId);

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

    // Title bar
    QWidget *m_titleBar;
    QPushButton *m_backBtn;
    QLabel *m_titleLabel;

    // Table
    QTableWidget *m_table;

    // Progress bar for scanning
    QProgressBar *m_scanProgress;

    // Buttons
    QWidget *m_buttonBar;
    QPushButton *m_addBtn;
    QPushButton *m_editBtn;
    QPushButton *m_deleteBtn;
    QPushButton *m_scanBtn;
};

#endif // DEVICELISTPAGE_H
