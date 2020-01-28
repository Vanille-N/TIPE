#pragma once

#include <QDataStream>
#include <QIODevice>
#include <QString>
#include <QFile>

enum loc {equator, pole} ;

class State {
public:
    State() ;

    void read (QString) ;
    void write (QString) ;
    double getAlpha () ;
    double getGamma () ;
    double getDelta () ;
    double getTrans () ;
    double getSig (loc) ;
    double getPhi () ;
    double getS (loc) ;
    double getT (loc) ;
    void setAlpha (double) ;
    void setGamma (double) ;
    void setDelta (double) ;
    void setTrans (double) ;
    void setSig (loc, double) ;
    void setPhi (double) ;
    void setS (loc, double) ;
    void setT (loc, double) ;

private:
    double transport ;
    double alpha ;
    double gamma ;
    double delta ;
    double phi ;
    double Sig [2] ;
    double S [2] ;
    double T [2] ;
};

