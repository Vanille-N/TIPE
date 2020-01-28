#include "state.h"

State::State() {
    S[equator] = 0.0 ;
    T[equator] = 0.0 ;
    S[pole] = 0.0 ;
    T[pole] = 0.0 ;
    phi = 0.0 ;
    alpha = 0.0 ;
    gamma = 0.0 ;
    delta = 0.0 ;
    transport = 0.0 ;
}

void State::read (QString input) {
    QFile f (input) ;
    if (!f.open(QIODevice::ReadOnly)) return ;
    QDataStream data (&f) ;
    data >> S[equator] ;
    data >> T[equator] ;
    data >> S[pole] ;
    data >> T[pole] ;
    data >> phi ;
    Sig[equator] = 0.0 ;
    Sig[pole] = 0.0 ;

}

void State::write (QString output) {
    QFile f (output) ;
    if (!f.open(QIODevice::WriteOnly)) return ;
    QDataStream data (&f) ;
    data << S[equator] ;
    data << T[equator] ;
    data << S[pole] ;
    data << T[pole] ;
    data << phi ;

}

double State::getAlpha () { return alpha ; }
double State::getGamma () { return gamma ; }
double State::getDelta () { return delta ; }
double State::getTrans () { return transport ; }
double State::getSig (loc l) { return Sig[l] ; }
double State::getPhi () { return phi ; }
double State::getS (loc l) { return S[l] ; }
double State::getT (loc l) { return T[l] ; }

void State::setAlpha (double val) { alpha = val ; }
void State::setGamma (double val) { gamma = val ; }
void State::setDelta (double val) { delta = val ; }
void State::setTrans (double val) { transport = val ; }
void State::setSig (loc l, double val) { Sig[l] = val ; }
void State::setPhi (double val) { phi = val ; }
void State::setS (loc l, double val) { S[l] = val ; }
void State::setT (loc l, double val) { T[l] = val ; }
