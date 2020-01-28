#pragma once

#include <QWidget>
#include "state.h"
#include "const.h"

#define ALPHA 1.7e-4
#define BETA 7.6e-4
#define RHO 1024
#define S0 32.3
#define T0 15

class Calculator {
public:
    Calculator (QWidget *, State *, Const *, Const *) ;
    void step () ;

private:
    double sigma (double, double) ;

    QWidget * m_refreshRoot ;
    State * m_Stt ;
    Const * m_Cst ;
    Const * m_Aim ;
};
