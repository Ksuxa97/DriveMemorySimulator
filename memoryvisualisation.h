#ifndef MEMORYVISUALISATION_H
#define MEMORYVISUALISATION_H

//#include "sector.h"

#include "styleset.h"
#include "sector.h"
#include "hexredactor.h"

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMap>

class MemoryVisualisation : public QWidget
{
    Q_OBJECT

private:
    QVector<Sector*> memoryPicture;
    int sectorsNumber = 0;
    int sectorSize = 0;
    QGridLayout *pictureLayout;
    HexRedactor *sectorRedactor;
    int sectorsOnPage = 180;
    QPushButton *downBtn;
    QPushButton *upBtn;
    QLabel *sectorInterval;
    QMap<QPair<int, int>, QColor> sectorGroups;
    bool lastPage = false;
    QWidget *parent;

public:
    explicit MemoryVisualisation(int, QWidget *parent);
    void drawSector(int, int);
    void drawAllSectors();
    void filledSectors(int, int);
    void newPageColor();
    void setSectorsNumber(int);
    int getSectorSize();
    int getSectorsNumber();

public slots:
    void clickedSector();
    void switchSectorPage();
    void setSectorSize(QString);
};

#endif // MEMORYVISUALISATION_H
