#include "styleset.h"

void StyleSet::setQLineEditStyle(QLineEdit *lineEdit, bool isReadable){
    lineEdit->setStyle(QStyleFactory::create("Fusion"));
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setReadOnly(isReadable);
    lineEdit->setStyleSheet("QLineEdit:focus{"
                            "border: 2px groove #1a1b1d;"
                            "border-radius: 4px;}");
}

void StyleSet::setQPushButtonStyle(QPushButton *pushButton){
    pushButton->setStyle(QStyleFactory::create("Fusion"));
    pushButton->setStyleSheet("background-color: #555658");
}

void StyleSet::setQComboBoxStyle(QComboBox *comboBox){
    comboBox->setStyle(QStyleFactory::create("Fusion"));
    comboBox->setStyleSheet("background-color: #555658");
}

void StyleSet::setBtnColor(QPushButton *btn, QColor color){
    QString backColor = QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue());
    btn->setStyleSheet(backColor);
}

void StyleSet::setLastBtnStyle(QPushButton *pushButton){
    pushButton->setFixedHeight(50);
    pushButton->setStyle(QStyleFactory::create("Fusion"));
    pushButton->setStyleSheet("font-size: 16pt");
}
