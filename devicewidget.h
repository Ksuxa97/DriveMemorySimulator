#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include "abstractdevice.h"
#include "diskdevice.h"
#include "flashdevice.h"
#include "styleset.h"
#include "memoryvisualisation.h"
#include "messagewindow.h"

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

class DeviceWidget : public QWidget
{
    Q_OBJECT

private:
    int device_id = 0;
    QGridLayout *deviceLayout;
    AbstractDevice *abstractDevice;
    DiskDevice *diskDevice;
    FlashDevice *flashDevice;
    MemoryVisualisation *deviceMemory;
    QLineEdit *resultEdit_1;
    QLineEdit *resultEdit_2;
    QPushButton *writeFileBtn;
    QPushButton *returnToMenuBtn;
    MessageWindow *msgBox;
    int memorySize = 0;
    int cacheSize = 0;
    QString unit_1;
    QString unit_2;
    QLineEdit *cacheEdit;
    QComboBox *unitBox_1;
    QLineEdit *memoryEdit;
    QComboBox *unitBox_2;

public:
    DeviceWidget(int id, QWidget *parent);
    void diskWidget();
    void flashWidget();
    void opticalWidget();
    void usbDriveWidget();
    void widgetTitle();
    void diskFieldsInscription();
    void flashFieldsInscription();
    void diskInputFields();
    void flashInputFields();
    void deviceBtns();
    void cacheToBytes(QString);
    void memoryToBytes(QString);
    QPushButton *getReturnToMenuBtn();
    ~DeviceWidget();

signals:
    void deviceInterfaceChanged(QString);
    void calculate();

public slots:
    void currentFieldsData(QString);
    void deviceInterfaces(QString);
    void writeInMemory();
    void checkingErrors();
    void setResultEdits();
};

#endif // DEVICEWIDGET_H
