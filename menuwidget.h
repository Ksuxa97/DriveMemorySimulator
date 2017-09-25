#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include "styleset.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSettings>
#include <QStyleFactory>

class MenuWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *menuLayout;
    QHBoxLayout *deviceBtnsLayout;
    QVBoxLayout *lastDevicesLayout;
    QPushButton *hddBtn;
    QPushButton *ssdBtn;
    QPushButton *floppyBtn;
    QPushButton *opticalBtn;
    QPushButton *flashBtn;
    QPushButton *_hddBtn;
    QPushButton *_ssdBtn;
    QPushButton *_floppyBtn;
    QPushButton *_opticalBtn;
    QPushButton *_flashBtn;
    QVector<QPushButton*> lastDevicesBtns;
    QSettings *settings;
    QWidget *lastUsedDevices;

public:
    MenuWidget(QWidget *parent);
    QPushButton* getHddBtn();
    QPushButton* getSsdBtn();
    QPushButton* getFloppyBtn();
    QPushButton* getOpticalBtn();
    QPushButton* getFlashBtn();
    QPushButton* getLUHddBtn();
    QPushButton* getLUSsdBtn();
    QPushButton* getLUFloppyBtn();
    QPushButton* getLUOpticalBtn();
    QPushButton* getLUFlashBtn();
    void createDeviceBtns();
    void switchLastBtns(QString);
    ~MenuWidget();

public slots:
    void chosenDevice();
};

#endif // MENUWIDGET_H
