#include "const.h"

Const::Const () {
    for (int c = 0; c < NBCST; c++) {
        m_constants[c] = 111.1 ;
    }
}

void Const::read (QString input) {
    QFile f (input) ;
    if (!f.open(QIODevice::ReadOnly)) return ;
    QDataStream data (&f);
    for (int i = 0; i < NBCST; i++) {
        data >> m_constants[i] ;
    }
}

void Const::write (QString output) {
    QFile f (output) ;
    if (!f.open(QIODevice::WriteOnly)) return ;
    QDataStream data (&f);
    for (int i = 0; i < NBCST; i++) {
        data << m_constants[i] ;
    }
}

double Const::get (cst c) {
    return m_constants[c] ;
}

void Const::set (cst c, double val) {
    m_constants[c] = val ;
}

void Const::aim (cst c, double val) {
    m_constants[c] = 0.9*m_constants[c] + 0.1*val ;
    // Smoother variation of constants : any modification is stretched out in an exponential manner
}

double Const::orderOfMagnitude (cst c) {
    double pow = 1.0 ;
    if (abs(m_constants[c]) <= 1e-10) return 1.0 ;
    while (pow < abs(m_constants[c])) { pow *= 10.0 ; }
    while (pow > abs(m_constants[c])) { pow *= 0.1 ; }
    return pow ;
}
