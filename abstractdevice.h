#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QFile>

class AbstractDevice : public QObject
{
    Q_OBJECT

protected:
    QString interface;
    float transferRate = 0;
    double memorySize = 0;
    int sectorSize = 0;
    int numberOfFilledSectors = 0;
    QFile *memoryFile;

public:
    AbstractDevice();
    void setTransferRate(float value);
    QString getInterface();
    float getTransferRate();
    double getMemorySize();
    int getSectorSize();
    QFile *setMemoryFile(QByteArray byteArray);
    void setFilledSectors(int);
    int getFilledSectors();
    ~AbstractDevice();

public slots:
    void setInterface(QString);
    void setMemorySize(QString);
    void setSectorSize(QString);
};

#endif // DEVICE_H
