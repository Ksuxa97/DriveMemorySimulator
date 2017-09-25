#include "messagewindow.h"

MessageWindow::MessageWindow(QWidget *parent) : QMessageBox(parent)
{
    setWindowTitle("DriveMemorySimulator");
    setStyleSheet("background-color: #2e2f31;\n color: white;");
    okBtn = this->addButton(QMessageBox::Ok);
    StyleSet::setQPushButtonStyle(okBtn);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void MessageWindow::emptySettings(){
    this->setIcon(QMessageBox::Warning);
    this->setText("Установлены не все параметры устройства");
    this->exec();
}

void MessageWindow::memoryOverflow(){
    this->setIcon(QMessageBox::Critical);
    this->setText("Недостаточно памяти");
    this->exec();
}

void MessageWindow::redundancy(int value){
    this->setIcon(QMessageBox::Information);
    this->setText(QString("Избыточность составляет %1 байт").arg(value));
    this->exec();
}
