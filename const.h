#pragma once

#include <QDataStream>
#include <QString>
#include <QFile>

#define NBCST 9

enum cst {M0, tauS, tauT, Se, Sp, Te, Tp, dt, lambda} ;

class Const {
public:
    Const () ;

    double orderOfMagnitude (cst) ;
    double get (cst) ;
    void write (QString) ;
    void read (QString) ;
    void set (cst, double) ;
    void aim (cst, double) ;

private:
    double m_constants [NBCST] ;
};
