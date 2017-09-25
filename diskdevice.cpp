#include "diskdevice.h"

DiskDevice::DiskDevice(QObject *parent) : AbstractDevice()
{
    if(QFile::exists("deviceMemory.bin")){
        QFile::remove("deviceMemory.bin");
    }
    memoryFile = new QFile("deviceMemory.bin");
}

int DiskDevice::getRPM()
{
    return rpm;
}

int DiskDevice::getCache()
{
    return cache;
}

int DiskDevice::getTracksNumber()
{
    return tracksNumber;
}

int DiskDevice::getCylindersNumber()
{
    return cylindersNumber;
}

int DiskDevice::getSidesNumber()
{
    return sidesNumber;
}

float DiskDevice::rotationalLatency()
{
    return (60000/rpm) * 0.5;
}

float DiskDevice::seekTime()
{
    return 1 + (tracksNumber/3) / cylindersNumber;
}

float DiskDevice::transferTime()
{
    return sectorSize/transferRate;
}

int DiskDevice::getLatency()
{
    return rotationalLatency() + seekTime() + transferTime();
}

int DiskDevice::getReadWriteSpeed()
{
    int tmp1 = memorySize / 1024;
    int tmp2 = tmp1 * 60;
    int tmp = tmp2 / rpm;
    return tmp;
}

DiskDevice::~DiskDevice()
{

}

void DiskDevice::setRPM(QString value)
{
    rpm = value.toInt();
}

void DiskDevice::setCache(QString value)
{
    cache = value.toInt();
}

void DiskDevice::setTracksNumber(QString value)
{
    tracksNumber = value.toInt();
}

void DiskDevice::setCylindersNumber(QString value)
{
    cylindersNumber = value.toInt();
}

void DiskDevice::setSidesNumber(QString value)
{
    sidesNumber = value.toInt();
}
