#ifndef HEXREDACTOR_H
#define HEXREDACTOR_H

#include "styleset.h"

#include <QWidget>
#include <QLineEdit>
#include <QFile>
#include <QTextEdit>
#include <QTableWidget>
#include <QStyleFactory>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollArea>
#include <QFileDialog>
#include <QStandardPaths>

class HexRedactor : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *editField;
    QFile *memoryFile;
    QByteArray sectorData;
    QTextEdit *redactor;
    QTableWidget *tableWidget;
    QGridLayout *redactorLayout;
    int sectorSize = 0;
    int sectorNumber = 0;
    QPushButton *saveBtn;
    QPushButton *saveAsBtn;

public:
    HexRedactor(int, int, QWidget *parent = 0);
    QString hexString(QByteArray&);
    void dataView();
    void redactorBtns();

signals:

public slots:
    void saveData();

};

#endif // HEXREDACTOR_H
