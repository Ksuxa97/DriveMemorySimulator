#include "mainwindow.h"

#include <QApplication>
#include <QAbstractButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QTextEdit>
#include <QComboBox>
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("DriveMemorySimulator");

    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setStyleSheet("background-color: #2e2f31;\n color: white;");

    setFixedSize(600, 620);

    menuWindow = new MenuWidget(this);
    mainLayout->addWidget(menuWindow);

    //коннекты для кнопок устройств
    connect(menuWindow->getHddBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
    connect(menuWindow->getSsdBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
    connect(menuWindow->getFloppyBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
    connect(menuWindow->getOpticalBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
    connect(menuWindow->getFlashBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
    //коннекты для кнопок последних используемых устройств
    connect(menuWindow->getLUHddBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
    connect(menuWindow->getLUSsdBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
    connect(menuWindow->getLUFloppyBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
    connect(menuWindow->getLUOpticalBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
    connect(menuWindow->getLUFlashBtn(), SIGNAL(clicked()), this, SLOT(showDeviceWindow()));
}

void MainWindow::showDeviceWindow(){
    if((sender() == menuWindow->getHddBtn()) || (sender() == menuWindow->getLUHddBtn())){
        deviceWindow = new DeviceWidget(1, this);
    }
    else if((sender() == menuWindow->getSsdBtn()) || (sender() == menuWindow->getLUSsdBtn())){
       deviceWindow = new DeviceWidget(2, this);
    }
    else if((sender() == menuWindow->getFloppyBtn()) || (sender() == menuWindow->getLUFloppyBtn())){
        deviceWindow = new DeviceWidget(3, this);
    }
    else if((sender() == menuWindow->getOpticalBtn()) || (sender() == menuWindow->getLUOpticalBtn())){
        deviceWindow = new DeviceWidget(4, this);
    }
    else if((sender() == menuWindow->getFlashBtn()) || (sender() == menuWindow->getLUFlashBtn())){
       deviceWindow = new DeviceWidget(5, this);
    }
    mainLayout->addWidget(deviceWindow);
    connect(deviceWindow->getReturnToMenuBtn(), SIGNAL(clicked()), menuWindow, SLOT(show()));
    connect(deviceWindow->getReturnToMenuBtn(), SIGNAL(clicked()), this, SLOT(deleteDevice()));
}

void MainWindow::deleteDevice(){
    delete deviceWindow;
}

MainWindow::~MainWindow()
{
}
