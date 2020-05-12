#pragma once

#include <QPushButton>
#include <QLCDNumber>
#include <QString>
#include <QLabel>
#include "consteditor.h"

class ConstDisplayer : public QPushButton {
    Q_OBJECT
public:
    ConstDisplayer (QString, QWidget *, Const *, Const *, cst, QString) ;
    ~ConstDisplayer () ;

public slots:
    void launchEditor () ;
    void refresh () ;
    void delEd () ;

private:
    QVBoxLayout * m_vbox ;
    QLCDNumber * m_lcd ;
    QString m_label ;
    QLabel * m_varname ;
    ConstEditor * m_ed ;
    Const * m_Cst ;
    Const * m_Aim ;
    cst m_c ;
};
