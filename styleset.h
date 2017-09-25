#ifndef STYLESET_H
#define STYLESET_H

#include <QString>
#include <QLineEdit>
#include <QStyleFactory>
#include <QPushButton>
#include <QComboBox>

class StyleSet
{
public:
    static void setQLineEditStyle(QLineEdit*, bool);
    static void setQPushButtonStyle(QPushButton*);
    static void setQComboBoxStyle(QComboBox*);
    static void setBtnColor(QPushButton*, QColor color);
    static void setLastBtnStyle(QPushButton*);


};

#endif // STYLESET_H
