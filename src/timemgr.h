#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QString>
#include <QLabel>
#include "const.h"

class TimeMgr : public QPushButton {
    Q_OBJECT
public:
    TimeMgr (QWidget * parent, Const * Cst) ;
    void tick () ;
    double clock () ;

private:
    QVBoxLayout * m_vbox ;
    QLCDNumber * m_lcd ;
    Const * m_Cst ;
    double TIME ;
};
