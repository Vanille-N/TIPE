#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QString>
#include <QLabel>
#include "state.h"

#define FLOWRT "----->"
#define FLOWLT "<-----"

class FlowDisplayer : public QPushButton {
    Q_OBJECT
public:
    FlowDisplayer (QWidget *, State *) ;

public slots:
    void refresh () ;

private:
    QVBoxLayout * m_vbox ;
    QLCDNumber * m_lcdPhi ;
    QLCDNumber * m_lcdAlpha ;
    QLCDNumber * m_lcdBeta ;
    QLCDNumber * m_lcdDelta ;
    QLCDNumber * m_lcdTrans ;
    QWidget * m_parent ;
    QLabel * m_surfaceFlow ;
    QLabel * m_deepFlow ;
    QLabel * m_label ;
    State * m_Stt ;
};

