#include "abstractdevice.h"

AbstractDevice::AbstractDevice()
{

}

void AbstractDevice::setTransferRate(float value)
{
    transferRate = value;
}

QString AbstractDevice::getInterface()
{
    return interface;
}

float AbstractDevice::getTransferRate()
{
    return transferRate;
}

double AbstractDevice::getMemorySize()
{
    return memorySize;
}

int AbstractDevice::getSectorSize()
{
    return sectorSize;
}

QFile *AbstractDevice::setMemoryFile(QByteArray byteArray)
{
    memoryFile->open(QIODevice::Append);
    memoryFile->seek(numberOfFilledSectors*sectorSize);
    memoryFile->write(byteArray);
    memoryFile->close();
}

void AbstractDevice::setFilledSectors(int value)
{
    numberOfFilledSectors += value;
}

int AbstractDevice::getFilledSectors()
{
    return numberOfFilledSectors;
}

AbstractDevice::~AbstractDevice()
{

}

void AbstractDevice::setInterface(QString value)
{
    interface = value;
}

void AbstractDevice::setMemorySize(QString value)
{
    memorySize = value.toDouble();
}

void AbstractDevice::setSectorSize(QString value)
{
    sectorSize = value.toInt();
}


