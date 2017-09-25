#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include "memoryvisualisation.h"

#include <QMessageBox>
#include <QPushButton>

class MessageWindow : QMessageBox
{
    Q_OBJECT

private:
    QPushButton *okBtn;

public:
    MessageWindow(QWidget *parent);
    void emptySettings();
    void memoryOverflow();
    void redundancy(int);
};

#endif // MESSAGEWINDOW_H
