#include "ssd.h"

SSD::SSD(QWidget *parent) : QWidget(parent)
{
    if(QFile::exists("ssdMemory.bin")){
        QFile::remove("ssdMemory.bin");
    }
    memoryFile = new QFile("ssdMemory.bin");
}

void SSD::setCache(QString value){
    cache = value.toInt();
}

void SSD::setInterface(QString value){
    interfaceType = value;
}

void SSD::setReadSpeed(QString value){
    readSpeed = value.toInt();
}

void SSD::setWriteSpeed(QString value){
    writeSpeed = value.toInt();
}

void SSD::setMemorySize(QString value){
    memorySize = value.toInt();
}

void SSD::setSectorSize(QString value){
    sectorSize = value.toInt();
}

void SSD::setMemoryFile(QByteArray fileData){
    memoryFile->open(QIODevice::WriteOnly);
    memoryFile->write(fileData);
    memoryFile->close();
}

int SSD::getReadIOPS(){
    readIOPS = readSpeed * 1024 / 4;
    return readIOPS;
}

int SSD::getWriteIOPS(){
    writeIOPS = writeSpeed * 1024 / 4;
    return writeIOPS;
}

int SSD::getSectorSize(){
    return sectorSize;
}


SSD::~SSD(){

}
