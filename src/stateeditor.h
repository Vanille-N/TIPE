#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QPalette>
#include <QSlider>
#include <QString>
#include <QLabel>
#include "state.h"
#include "metavars.h"

class StateEditor : public QWidget {
    Q_OBJECT
public:
    StateEditor(QVector<State *> &, loc, QString, QWidget *) ;

public slots:
    void refresh () ;
    void incrOneS () ;
    void incrTthS () ;
    void incrHthS () ;
    void decrOneS () ;
    void decrTthS () ;
    void decrHthS () ;
    void incrOneT () ;
    void incrTthT () ;
    void incrHthT () ;
    void decrOneT () ;
    void decrTthT () ;
    void decrHthT () ;


private:
    void chvalS (double) ;
    void chvalT (double) ;

    QPushButton * m_okButton ;
    QGridLayout * m_buttonsS ;
    QGridLayout * m_buttonsT ;
    QPushButton * m_upOneS ;
    QPushButton * m_upTthS ;
    QPushButton * m_upHthS ;
    QPushButton * m_dnOneS ;
    QPushButton * m_dnTthS ;
    QPushButton * m_dnHthS ;
    QPushButton * m_upOneT ;
    QPushButton * m_upTthT ;
    QPushButton * m_upHthT ;
    QPushButton * m_dnOneT ;
    QPushButton * m_dnTthT ;
    QPushButton * m_dnHthT ;
    QVBoxLayout * m_vbox ;
    QHBoxLayout * m_hbox ;
    QVBoxLayout * m_Sbox ;
    QVBoxLayout * m_Tbox ;
    QLCDNumber * m_lcdS ;
    QLCDNumber * m_lcdT ;
    QWidget * m_parent ;
    QString m_param ;
    QVector<State *> m_Stt ;
    loc m_l ;
};
