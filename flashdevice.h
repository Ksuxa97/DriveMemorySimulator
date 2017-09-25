#ifndef FLASHDEVICE_H
#define FLASHDEVICE_H

#include "abstractdevice.h"

#include <QObject>

class FlashDevice : public AbstractDevice
{
    Q_OBJECT

private:
    int readSpeed = 0;
    int writeSpeed = 0;
    int readIOPS = 0;
    int writeIOPS = 0;

public:
    FlashDevice(QObject *parent);
    int getReadSpeed();
    int getWriteSpeed();
    int getReadIOPS();
    int getWriteIOPS();
    ~FlashDevice();

public slots:
    void setReadSpeed(QString);
    void setWriteSpeed(QString);
};

#endif // FLASHDEVICE_H
