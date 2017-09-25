#include "flashdevice.h"

FlashDevice::FlashDevice(QObject *parent) : AbstractDevice()
{
    if(QFile::exists("deviceMemory.bin")){
        QFile::remove("deviceMemory.bin");
    }
    memoryFile = new QFile("deviceMemory.bin");
}

int FlashDevice::getReadSpeed()
{
    return readSpeed;
}

int FlashDevice::getWriteSpeed()
{
    return writeSpeed;
}

int FlashDevice::getReadIOPS()
{
    return readSpeed * 1024 / 4;
}

int FlashDevice::getWriteIOPS()
{
    return writeSpeed * 1024 / 4;
}

FlashDevice::~FlashDevice()
{

}

void FlashDevice::setReadSpeed(QString value)
{
    readSpeed = value.toInt();
}

void FlashDevice::setWriteSpeed(QString value)
{
    writeSpeed = value.toInt();
}
