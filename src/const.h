#pragma once

#include <QDataStream>
#include <QString>
#include <QFile>
#include "metavars.h"

enum cst {M0, tauS, tauT, Se, Sp, Te, Tp, dt, lambda} ;

class Const {
public:
    Const (bool) ;

    double orderOfMagnitude (cst) ;
    double get (cst) ;
    void write (QString) ;
    void read (QString) ;
    void set (cst, double) ;
    void aim (cst, double) ;

private:
    double m_constants [NB_CST] ;
    double m_offset [NB_CST] ;
#if SMOOTHEN_EQ == 1
    double m_smoothen [NB_CST] ;
#endif
};
