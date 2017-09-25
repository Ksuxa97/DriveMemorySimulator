#include "sector.h"

Sector::Sector(QWidget *parent) : QPushButton(parent)
{
    this->setStyleSheet("background-color: white;\n width: 40;\n height: 20;");
}

void Sector::setSectorNumber(int number){
    sectorNumber = number;
}

int Sector::getSectorNumber(){
    return sectorNumber;
}
