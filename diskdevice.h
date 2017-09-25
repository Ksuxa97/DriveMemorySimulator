#ifndef DISKDEVICE_H
#define DISKDEVICE_H

#include "abstractdevice.h"

#include <QObject>

class DiskDevice : public AbstractDevice
{
    Q_OBJECT

private:
    int rpm = 0;
    int cache = 0;
    int tracksNumber = 0;
    int cylindersNumber = 0;
    int sidesNumber = 0;

public:
    DiskDevice(QObject *parent);
    int getRPM();
    int getCache();
    int getTracksNumber();
    int getCylindersNumber();
    int getSidesNumber();
    float rotationalLatency();
    float seekTime();
    float transferTime();
    int getLatency();
    int getReadWriteSpeed();
    ~DiskDevice();


public slots:
    void setRPM(QString value);
    void setCache(QString value);
    void setTracksNumber(QString value);
    void setCylindersNumber(QString value);
    void setSidesNumber(QString value);
};

#endif // DISKDEVICE_H
