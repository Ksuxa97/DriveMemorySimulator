#ifndef SECTOR_H
#define SECTOR_H

#include <QWidget>
#include <QPushButton>

class Sector : public QPushButton
{
private:
    int sectorNumber = 0;

public:
    Sector(QWidget *parent);
    void setSectorNumber(int);
    int getSectorNumber();
};

#endif // SECTOR_H
