#ifndef SSD_H
#define SSD_H

#include <QWidget>
#include <QFile>

class SSD : public QWidget
{
    Q_OBJECT

private:
    int cache = 0;
    int readSpeed = 0;
    int writeSpeed = 0;
    QString interfaceType;
    int memorySize = 0;
    int sectorSize = 0;
    int readIOPS = 0;
    int writeIOPS = 0;
    QFile *memoryFile;

public:
    explicit SSD(QWidget *parent);
    int getReadIOPS();
    int getWriteIOPS();
    QFile* getMemoryFile();
    void setMemoryFile(QByteArray);
    int getSectorSize();
    ~SSD();

public slots:
    void setCache(QString);
    void setInterface(QString);
    void setReadSpeed(QString);
    void setWriteSpeed(QString);
    void setMemorySize(QString);
    void setSectorSize(QString);
};

#endif // SSD_H
