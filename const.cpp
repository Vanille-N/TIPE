#include "const.h"

Const::Const (bool variable) {
    for (int c = 0; c < NB_CST; c++) {
        m_constants[c] = 111.1 ;
        m_offset[c] = 1 + (double)(qrand() % 101 - 51) / 50 * variable * VARIABILITY ;
    }
    read("_default_.cst") ;
#if SMOOTHEN_EQ == 1
    for (int i = 0; i < NB_CST; i++) {
        m_smoothen[i] = m_constants[i] ;
    }
#endif
}

void Const::read (QString input) {
    QFile f (input) ;
    if (!f.open(QIODevice::ReadOnly)) return ;
    QDataStream data (&f);
    for (int i = 0; i < NB_CST; i++) {
        data >> m_constants[i] ;
        m_constants[i] *= m_offset[i] ;
    }
}

void Const::write (QString output) {
    QFile f (output) ;
    if (!f.open(QIODevice::WriteOnly)) return ;
    QDataStream data (&f);
    for (int i = 0; i < NB_CST; i++) {
        data << m_constants[i] ;
    }
}

double Const::get (cst c) {
    return m_constants[c] ;
}

void Const::set (cst c, double val) {
    m_constants[c] = val * m_offset[c] ;
}

void Const::aim (cst c, double val) {
#if SMOOTHEN_EQ == 0
    m_constants[c] = 0.9*m_constants[c] + 0.1*val*m_offset[c] ;
    // Smoother variation of constants : any modification is stretched out in an exponential manner
#elif SMOOTHEN_EQ == 1
    m_smoothen[c] = 0.8*m_smoothen[c] + 0.2*val*m_offset[c] ;
    m_constants[c] = 0.8*m_constants[c] + 0.2*m_smoothen[c] ;
#endif
}

double Const::orderOfMagnitude (cst c) {
    double pow = 1.0 ;
    if (abs(m_constants[c]) <= 1e-10) return 1.0 ;
    while (pow < abs(m_constants[c])) { pow *= 10.0 ; }
    while (pow > abs(m_constants[c])) { pow *= 0.1 ; }
    return pow ;
}
