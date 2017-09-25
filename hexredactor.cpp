#include "hexredactor.h"

HexRedactor::HexRedactor(int sectorNumber, int sectorSize, QWidget *parent) : QWidget(parent)
{
    setWindowTitle("DriveMemorySimulator");
    setStyleSheet("background-color: #2e2f31;\n color: white;");
    setFixedSize(456, 435);

    redactorLayout = new QGridLayout(this);
    redactorLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(redactorLayout);

    this->sectorSize = sectorSize;
    this->sectorNumber = sectorNumber;

    memoryFile = new QFile("deviceMemory.bin");

    memoryFile->open(QIODevice::ReadOnly);
    memoryFile->seek(sectorSize*sectorNumber);
    sectorData = memoryFile->read(sectorSize);
    memoryFile->close();

    dataView();
    redactorBtns();
}

QString HexRedactor::hexString(QByteArray &sectorData){

    QString mass = sectorData.toHex();

    QString out;
        if (sectorData.length() > 0) {
            out = QString("%1").arg(mass[0]);
            out.append(QString("%1").arg(mass[1]));
        }
        for (int i = 2; i < sectorData.length(); ++i) {
            out.append(QString(" %1").arg(mass[i]));
            ++i;
            out.append(QString("%1").arg(mass[i]));
        }
        return out;
}

void HexRedactor::dataView(){
    tableWidget = new QTableWidget(sectorSize/16, 16, this);
    tableWidget->setFixedSize(455, 400);

    tableWidget->setStyle(QStyleFactory::create("Fusion"));
    QScrollArea *scroll = new QScrollArea();
    //QScrollBar *scroll = new QScrollBar();
    scroll->setStyle(QStyleFactory::create("Macintosh"));
    tableWidget->setVerticalScrollBar(scroll->verticalScrollBar());


    QString mass = sectorData.toHex();

    int count = 0;

    for(int i = 0; i < 16; ++i){
        tableWidget->setColumnWidth(i, 25);
        QString j;
        j.setNum(i, 16);
        QTableWidgetItem *hnm_1 = new QTableWidgetItem(QString("0%1").arg(j));
        hnm_1->setBackground(QBrush(QColor(46, 47, 49)));
        tableWidget->setHorizontalHeaderItem(i, hnm_1);

    }

    for(int i = 0; i < sectorSize/16; ++i){
        tableWidget->setRowHeight(i, 25);
        QString j;
        j.setNum(i*16, 16);
        QTableWidgetItem *vnm_1;
        if(i == 0){
            vnm_1 = new QTableWidgetItem(QString("000%1").arg(j));
        }
        else if(i <= 15){
            vnm_1 = new QTableWidgetItem(QString("00%1").arg(j));
        }
        else if(i <= 255){
            vnm_1 = new QTableWidgetItem(QString("0%1").arg(j));
        }

        tableWidget->setVerticalHeaderItem(i, vnm_1);
    }

    for(int i = 0; i < sectorSize/16; ++i){
        for(int j = 0; j < 16; ++j){
            QLineEdit *edit = new QLineEdit(tr("%1%2").arg(mass[count]).arg(mass[count+1]), tableWidget);
            edit->setInputMask("HH");
            edit->setFrame(false);
            edit->setAlignment(Qt::AlignCenter);
            tableWidget->setCellWidget(i, j, edit);
            count += 2;
        }
    }

    redactorLayout->addWidget(tableWidget, 0, 0, 1, 12);
}

void HexRedactor::redactorBtns(){
    saveBtn = new QPushButton("Сохранить", this);
    StyleSet::setQPushButtonStyle(saveBtn);
    redactorLayout->addWidget(saveBtn, 1, 5, 1, 3);
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveData()));

    saveAsBtn = new QPushButton("Сохранить как", this);
    StyleSet::setQPushButtonStyle(saveAsBtn);
    redactorLayout->addWidget(saveAsBtn, 1, 8, 1, 3);
    connect(saveAsBtn, SIGNAL(clicked()), this, SLOT(saveData()));
}

void HexRedactor::saveData(){
    QString tmpString;
    QByteArray tmpArray;

    for(int i = 0; i < sectorSize/16; ++i){
        for(int j = 0; j < 16; ++j){
            tmpString.append(tableWidget->item(i, j)->text());

        }
    }

    tmpArray = QByteArray::fromHex(tmpString.toLatin1());

    if(sender() == saveBtn){
        memoryFile->open(QIODevice::Append);
        memoryFile->seek(sectorSize*sectorNumber);
        memoryFile->write(tmpArray);
        memoryFile->close();
    }

    if(sender() == saveAsBtn){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                   tr("All files (*.*)"));
        QFile *fileToSave = new QFile(fileName);
        fileToSave->open(QIODevice::WriteOnly);
        fileToSave->write(tmpArray);
        fileToSave->close();
    }

}
