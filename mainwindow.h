#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QVector>
#include <QHBoxLayout>

#include "diskdevice.h"
#include "flashdevice.h"
#include "menuwidget.h"
#include "devicewidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *mainLayout;
    DeviceWidget *deviceWindow;
    MenuWidget *menuWindow;

public:
    MainWindow(QWidget *parent = 0);
    void clearScr();
    void createDeviceBtns();
    ~MainWindow();

public slots:
    void showDeviceWindow();
    void deleteDevice();
};

#endif // MAINWINDOW_H
