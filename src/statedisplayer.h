#pragma once

#include <QPushButton>
#include <QLCDNumber>
#include <QString>
#include <QLabel>
#include "stateeditor.h"
#include "state.h"

class StateDisplayer : public QPushButton {
    Q_OBJECT
public:
    StateDisplayer (QString, QWidget *, QVector<State *> &, loc) ;
    ~StateDisplayer () ;

public slots:
    void launchEditor () ;
    void refresh () ;
    void delEd () ;

private:
    QVBoxLayout * m_vbox ;
    QLCDNumber * m_lcdS ;
    QLCDNumber * m_lcdT ;
    QLCDNumber * m_lcdSig ;
    QString m_label ;
    QLabel * m_varname ;
    QLabel * m_SigLabel ;
    QLabel * m_SLabel ;
    QLabel * m_TLabel ;
    StateEditor * m_ed ;
    QVector<State *> m_Stt ;
    loc m_l ;
};
