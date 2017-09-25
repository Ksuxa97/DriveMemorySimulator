#include "memoryvisualisation.h"

MemoryVisualisation::MemoryVisualisation(int sizeY, QWidget *parent) : QWidget(parent)
{
    setMinimumSize(588, sizeY);

    pictureLayout = new QGridLayout(this);

    this->parent = parent;

    pictureLayout->setSpacing(0);
}

void MemoryVisualisation::drawAllSectors()
{
    sectorInterval = new QLabel("0 - " +
                        QString::number(sectorsOnPage-1), this);
    pictureLayout->addWidget(sectorInterval, 0, 0, 1, 3);

    downBtn = new QPushButton(this);
    downBtn->setIcon(QIcon(":/images/down.png"));
    downBtn->setIconSize(QSize(20, 20));
    downBtn->setStyleSheet("border-style: outset;\n");
    downBtn->setCursor(Qt::PointingHandCursor);
    pictureLayout->addWidget(downBtn, 0, 13);

    connect(downBtn, SIGNAL(clicked()), this, SLOT(switchSectorPage()));

    upBtn = new QPushButton(this);
    upBtn->setIcon(QIcon(":/images/up.png"));
    upBtn->setIconSize(QSize(20, 20));
    upBtn->setStyleSheet("border-style: outset;\n");
    upBtn->setCursor(Qt::PointingHandCursor);
    pictureLayout->addWidget(upBtn, 0, 14);

    connect(upBtn, SIGNAL(clicked()), this, SLOT(switchSectorPage()));

    //создание секторов
    for(int i = 0; i < sectorsOnPage; ++i){
        memoryPicture.push_back(new Sector(this));
        memoryPicture[i]->setSectorNumber(i);

        connect(memoryPicture[i], SIGNAL(clicked()), this, SLOT(clickedSector()));

        if(memoryPicture[i]->getSectorNumber() >= sectorsNumber){
            StyleSet::setBtnColor(memoryPicture[i], QColor(46, 47, 49));
            memoryPicture[i]->setStyleSheet("border-style: outset;\n width: 40;\n height: 20;");
            memoryPicture[i]->setEnabled(false);
            lastPage = true;
        }
        else{
            memoryPicture[i]->setCursor(Qt::PointingHandCursor);
        }
    }
    //вывод секторов
    int count = 0;
    for(int i = 0; count < sectorsOnPage; ++i)
    {
        for(int j = 0; j < 15; ++j, ++count)
        {
            pictureLayout->addWidget(memoryPicture[count], i + 1, j);
        }
    }

    pictureLayout->setMargin(5);
}

void MemoryVisualisation::switchSectorPage(){

    if(sender() == downBtn){
        if(!lastPage){
            //смена индексов секторов
            foreach (Sector *sector, memoryPicture) {
                sector->setSectorNumber(sector->getSectorNumber()+180);
            }
            newPageColor();
            sectorInterval = new QLabel(QString::number(memoryPicture.first()->getSectorNumber()) + " - " +
                                QString::number(memoryPicture.last()->getSectorNumber()), this);
            pictureLayout->addWidget(sectorInterval, 0, 0, 1, 3);
        }
    }
    if(sender() == upBtn){
        if(memoryPicture[0]->getSectorNumber() != 0){
            foreach (Sector *sector, memoryPicture) {
                if(lastPage){
                    if(sector->getSectorNumber() >= sectorsNumber){
                        StyleSet::setBtnColor(sector, QColor(255, 255, 255));
                        sector->setEnabled(true);
                    }
                }
                sector->setSectorNumber(sector->getSectorNumber()-180);
            }
            lastPage = false;
            newPageColor();
            sectorInterval = new QLabel(QString::number(memoryPicture.first()->getSectorNumber()) + " - " +
                                QString::number(memoryPicture.last()->getSectorNumber()), this);
            pictureLayout->addWidget(sectorInterval, 0, 0, 1, 3);
        }
    }
}

void MemoryVisualisation::newPageColor(){
    //перекраска секторов
    foreach (Sector *sector, memoryPicture) {
        StyleSet::setBtnColor(sector, QColor(255, 255, 255));
    }

    for(auto it = sectorGroups.begin(); it != sectorGroups.end(); ++it){
        if(it.key().second >= memoryPicture[0]->getSectorNumber()){
            //если начало блока за страницей
            if(it.key().first < memoryPicture[0]->getSectorNumber()){
                foreach (Sector *sector, memoryPicture) {
                    if(sector->getSectorNumber() <= it.key().second){
                        StyleSet::setBtnColor(sector, it.value());
                    }
                }
            }
            else{
                foreach (Sector *sector, memoryPicture) {
                    if((sector->getSectorNumber() >= it.key().first) && (sector->getSectorNumber() < it.key().second)){
                        StyleSet::setBtnColor(sector, it.value());
                    }
                }
            }
        }
    }

    foreach (Sector *sector, memoryPicture) {
        if(sector->getSectorNumber() >= sectorsNumber){
            StyleSet::setBtnColor(sector, QColor(46, 47, 49));
            sector->setStyleSheet("border-style: outset;\n width: 40;\n height: 20;");
            sector->setEnabled(false);
            lastPage = true;
        }
    }
}

void MemoryVisualisation::clickedSector(){
    //StyleSet::setBtnColor(memoryPicture.first(), QColor(46, 47, 49));

    foreach (Sector *sector, memoryPicture) {
        if(sender() == sector){
            parent->setWindowModality(Qt::WindowModal);
            sectorRedactor = new HexRedactor(sector->getSectorNumber(), sectorSize);
            sectorRedactor->show();
        }
    }
}

void MemoryVisualisation::filledSectors(int numberOfSectors, int position){

    int r = qrand() % 255;
    int g = qrand() % 255;
    int b = qrand() % 255;

    sectorGroups.insert(QPair<int,int>(position, position+numberOfSectors), QColor(r, g, b));

    foreach (Sector *sector, memoryPicture) {
        if((sector->getSectorNumber() >= position) & (sector->getSectorNumber() < (position+numberOfSectors))){
            StyleSet::setBtnColor(sector, QColor(r, g, b));
        }
    }

//    for(int i = position; i < (position + numberOfSectors); ++i){
//        StyleSet::setBtnColor(memoryPicture[i], QColor(r, g, b));
//    }
}

void MemoryVisualisation::setSectorsNumber(int value){
    sectorsNumber = value;
}

void MemoryVisualisation::setSectorSize(QString value){
    sectorSize = value.toInt();
}

int MemoryVisualisation::getSectorSize(){
    return sectorSize;
}

int MemoryVisualisation::getSectorsNumber(){
    return sectorsNumber;
}
