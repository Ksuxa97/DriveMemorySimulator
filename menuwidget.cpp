#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent)
{
    //общий слой
    menuLayout = new QVBoxLayout(this);
    menuLayout->setContentsMargins(0, 0, 0, 0);

    //слой для кнопок устройств
    deviceBtnsLayout = new QHBoxLayout;
    deviceBtnsLayout->setContentsMargins(20, 100, 20, 115);
    menuLayout->addLayout(deviceBtnsLayout);

    //виджет для кнопок последних используемых устройств
    lastUsedDevices = new QWidget(this);
    lastUsedDevices->setFixedSize(600, 300);
    lastUsedDevices->setStyleSheet("background-color: #555658;");

    //слой для кнопок последних используемых устройств
    lastDevicesLayout = new QVBoxLayout(lastUsedDevices);
    lastUsedDevices->setLayout(lastDevicesLayout);

    menuLayout->addWidget(lastUsedDevices);

    createDeviceBtns();

    //организация хранения последних используемых устройств
    settings = new QSettings("ksuInc", "Drive memory simulator");

    if(!settings->contains("device1")){
        settings->setValue("device1", " ");
        settings->setValue("device2", " ");
        settings->setValue("device3", " ");
    }
    else{
        switchLastBtns(settings->value("device1").toString());
        switchLastBtns(settings->value("device2").toString());
        switchLastBtns(settings->value("device3").toString());
    }
}

void MenuWidget::createDeviceBtns(){
    hddBtn = new QPushButton(QIcon(":/images/hdd.png"), "", this);
    hddBtn->setIconSize(QSize(64, 100));
    hddBtn->setStyleSheet("border-style: outset;\n color: white;");
    hddBtn->setCursor(Qt::PointingHandCursor);
    deviceBtnsLayout->addWidget(hddBtn);

    ssdBtn = new QPushButton(QIcon(":/images/ssd.png"), "", this);
    ssdBtn->setIconSize(QSize(110, 100));
    ssdBtn->setStyleSheet("border-style: outset;\n color: white;");
    ssdBtn->setCursor(Qt::PointingHandCursor);
    deviceBtnsLayout->addWidget(ssdBtn);

    floppyBtn = new QPushButton(QIcon(":/images/floppy.png"), "", this);
    floppyBtn->setIconSize(QSize(64, 100));
    floppyBtn->setStyleSheet("border-style: outset;\n color: white;");
    floppyBtn->setCursor(Qt::PointingHandCursor);
    deviceBtnsLayout->addWidget(floppyBtn);

    opticalBtn = new QPushButton(QIcon(":/images/optical.png"), "", this);
    opticalBtn->setIconSize(QSize(80, 100));
    opticalBtn->setStyleSheet("border-style: outset;\n color: white;");
    opticalBtn->setCursor(Qt::PointingHandCursor);
    deviceBtnsLayout->addWidget(opticalBtn);

    flashBtn = new QPushButton(QIcon(":/images/flash.png"), "", this);
    flashBtn->setIconSize(QSize(80, 100));
    flashBtn->setStyleSheet("border-style: outset;\n color: white;");
    flashBtn->setCursor(Qt::PointingHandCursor);
    deviceBtnsLayout->addWidget(flashBtn);

    _hddBtn = new QPushButton("Жесткий диск");
    StyleSet::setLastBtnStyle(_hddBtn);
    _ssdBtn = new QPushButton("Твердотельный накопитель");
    StyleSet::setLastBtnStyle(_ssdBtn);
    _floppyBtn = new QPushButton("Дискета");
    StyleSet::setLastBtnStyle(_floppyBtn);
    _opticalBtn = new QPushButton("Оптический диск");
    StyleSet::setLastBtnStyle(_opticalBtn);
    _flashBtn = new QPushButton("USB-флэш-накопитель");
    StyleSet::setLastBtnStyle(_flashBtn);

    connect(hddBtn, SIGNAL(clicked()), this, SLOT(hide()));
    connect(ssdBtn, SIGNAL(clicked()), this, SLOT(hide()));
    connect(floppyBtn, SIGNAL(clicked()), this, SLOT(hide()));
    connect(opticalBtn, SIGNAL(clicked()), this, SLOT(hide()));
    connect(flashBtn, SIGNAL(clicked()), this, SLOT(hide()));

    connect(_hddBtn, SIGNAL(clicked()), this, SLOT(hide()));
    connect(_ssdBtn, SIGNAL(clicked()), this, SLOT(hide()));
    connect(_floppyBtn, SIGNAL(clicked()), this, SLOT(hide()));
    connect(_opticalBtn, SIGNAL(clicked()), this, SLOT(hide()));
    connect(_flashBtn, SIGNAL(clicked()), this, SLOT(hide()));

    connect(hddBtn, SIGNAL(clicked()), this, SLOT(chosenDevice()));
    connect(ssdBtn, SIGNAL(clicked()), this, SLOT(chosenDevice()));
    connect(floppyBtn, SIGNAL(clicked()), this, SLOT(chosenDevice()));
    connect(opticalBtn, SIGNAL(clicked()), this, SLOT(chosenDevice()));
    connect(flashBtn, SIGNAL(clicked()), this, SLOT(chosenDevice()));
}

void MenuWidget::chosenDevice(){
    QString device1, device2, device3;
    device1 = settings->value("device1").toString();
    device2 = settings->value("device2").toString();
    device3 = settings->value("device3").toString();

    //QString tmp = settings->value("device1").toString();

    if(sender() == hddBtn){
        if((device1 != "Жесткий диск") & (device2 != "Жесткий диск") & (device3 != "Жесткий диск")){
            settings->setValue("device1", "Жесткий диск");
        }
    }
    else if(sender() == ssdBtn){
        if((device1 != "Твердотельный накопитель") & (device2 != "Твердотельный накопитель") & (device3 != "Твердотельный накопитель")){
            settings->setValue("device1", "Твердотельный накопитель");
        }
    }
    else if(sender() == floppyBtn){
        if((device1 != "Дискета") & (device2 != "Дискета")  & (device3 != "Дискета")){
            settings->setValue("device1", "Дискета");
        }
    }
    else if(sender() == opticalBtn){
        if((device1 != "Оптический диск") & (device2 != "Оптический диск") & (device3 != "Оптический диск")){
           settings->setValue("device1", "Оптический диск");
        }
    }
    else if(sender() == flashBtn){
        if((device1 != "USB-флэш-накопитель") & (device2 != "USB-флэш-накопитель") & (device3 != "USB-флэш-накопитель")){
            settings->setValue("device1", "USB-флэш-накопитель");
        }
    }

    if(device1 != settings->value("device1").toString()){
        settings->setValue("device3", device2);
        settings->setValue("device2", device1);
        switchLastBtns(settings->value("device1").toString());
    }
}

void MenuWidget::switchLastBtns(QString value){
    if(lastDevicesBtns.size() > 3){
        lastDevicesLayout->removeWidget(lastDevicesBtns.front());
        lastDevicesBtns.pop_front();
    }

    if(value == "Жесткий диск"){
        lastDevicesBtns.push_back(_hddBtn);
    }
    else if(value == "Твердотельный накопитель"){
        lastDevicesBtns.push_back(_ssdBtn);
    }
    else if(value == "Дискета"){
        lastDevicesBtns.push_back(_floppyBtn);
    }
    else if(value == "Оптический диск"){
        lastDevicesBtns.push_back(_opticalBtn);
    }
    else if(value == "USB-флэш-накопитель"){
        lastDevicesBtns.push_back(_flashBtn);
    }
    else{
        QPushButton *tmpBtn = new QPushButton(value);
        tmpBtn->setStyleSheet("border: outset;");
        tmpBtn->setEnabled(false);
        lastDevicesBtns.push_back(tmpBtn);
    }

    if(lastDevicesBtns.size() > 3){
        lastDevicesLayout->removeWidget(lastDevicesBtns.front());
        lastDevicesBtns.pop_front();
    }

    lastDevicesLayout->addWidget(lastDevicesBtns.back());
}

QPushButton* MenuWidget::getHddBtn(){
    return hddBtn;
}

QPushButton* MenuWidget::getSsdBtn(){
    return ssdBtn;
}

QPushButton* MenuWidget::getFloppyBtn(){
    return floppyBtn;
}

QPushButton* MenuWidget::getOpticalBtn(){
    return opticalBtn;
}

QPushButton* MenuWidget::getFlashBtn(){
    return flashBtn;
}

QPushButton* MenuWidget::getLUHddBtn(){
    return _hddBtn;
}

QPushButton* MenuWidget::getLUSsdBtn(){
    return _ssdBtn;
}

QPushButton* MenuWidget::getLUFloppyBtn(){
    return _floppyBtn;
}

QPushButton* MenuWidget::getLUOpticalBtn(){
    return _opticalBtn;
}

QPushButton* MenuWidget::getLUFlashBtn(){
    return _flashBtn;
}

MenuWidget::~MenuWidget(){

}
