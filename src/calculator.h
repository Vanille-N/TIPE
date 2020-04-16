#pragma once

#include <QWidget>
#include <QVector>
#include "state.h"
#include "const.h"
#include "metavars.h"

#if CSTVAL == 0
#define ALPHA 1.7e-4
#define BETA 7.6e-4
#define RHO 1024
#define S0 32.3
#define T0 15
#else
#define ALPHA 2.976e-4
#define BETA 7.383e-4
#define RHO 1023.0
#define S0 35.0
#define T0 25.0
#endif

class Calculator {
public:
    Calculator (QWidget *, QVector<State *> &, QVector<Const *> &, Const *, bool *, bool *) ;
    void step () ;

private:
    QWidget * m_refreshRoot ;
    QVector<State *> m_Stt ;
    QVector<Const *> m_Cst ;
    Const * m_Aim ;
    bool * CPL ;
    bool * EQM ;
};

double sigma (double, double) ;
