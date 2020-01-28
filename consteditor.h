#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QPalette>
#include <QSlider>
#include <QString>
#include <QLabel>
#include "const.h"

class ConstEditor : public QWidget {
    Q_OBJECT
public:
    ConstEditor(Const *, cst, QString, QWidget *) ;

public slots:
    void refresh () ;
    void incrOne () ;
    void incrTth () ;
    void incrHth () ;
    void decrOne () ;
    void decrTth () ;
    void decrHth () ;


private:
    void chval (double) ;

    QGridLayout * m_buttons ;
    QPushButton * m_okButton ;
    QPushButton * m_upOne ;
    QPushButton * m_upTth ;
    QPushButton * m_upHth ;
    QPushButton * m_dnOne ;
    QPushButton * m_dnTth ;
    QPushButton * m_dnHth ;
    QVBoxLayout * m_vbox ;
    QLCDNumber * m_lcd ;
    QWidget * m_parent ;
    QString m_param ;
    Const * m_Aim ;
    cst m_c ;
};
