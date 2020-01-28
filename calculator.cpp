#include "calculator.h"

Calculator::Calculator (QWidget * parent, State * Stt, Const * Cst, Const * Aim) {
    m_Stt = Stt ;
    m_Cst = Cst ;
    m_Aim = Aim ;
    m_refreshRoot = parent ;
}

inline double Calculator::sigma (double S, double T) {
    return RHO * (-ALPHA*(T-T0) + BETA*(S-S0)) ;
}

void Calculator::step () {
    double _Te = m_Stt->getT(equator) ;
    double _Tp = m_Stt->getT(pole) ;
    double _Se = m_Stt->getS(equator) ;
    double _Sp = m_Stt->getS(pole) ;
    double _Te_ = m_Cst->get(Te) ;
    double _Tp_ = m_Cst->get(Tp) ;
    double _Se_ = m_Cst->get(Se) ;
    double _Sp_ = m_Cst->get(Sp) ;
    double _M0_ = m_Cst->get(M0) ;
    double _lambda_ = m_Cst->get(lambda) ;
    double _tauT_ = m_Cst->get(tauT) ;
    double _tauS_ = m_Cst->get(tauS) ;
    double _dt_ = m_Cst->get(dt) ;
    double sigP = sigma(_Sp, _Tp) ;
    double sigE = sigma(_Se, _Te) ;
    double phi = _lambda_ * (sigP - sigE) ;
    double dTe = (_Tp - _Te) * (abs(phi) / _M0_) + (_Te_ - _Te) / _tauT_ ;
    double dTp = (_Te - _Tp) * (abs(phi) / _M0_) + (_Tp_ - _Tp) / _tauT_ ;
    double dSe = (_Sp - _Se) * (abs(phi) / _M0_) + (_Se_ - _Se) / _tauS_ ;
    double dSp = (_Se - _Sp) * (abs(phi) / _M0_) + (_Sp_ - _Sp) / _tauS_ ;
    m_Stt->setPhi(phi) ;
    m_Stt->setS(pole, _Sp + dSp*_dt_) ;
    m_Stt->setS(equator, _Se + dSe*_dt_) ;
    m_Stt->setT(pole, _Tp + dTp*_dt_) ;
    m_Stt->setT(equator, _Te + dTe*_dt_) ;
    m_Stt->setSig(pole, sigP) ;
    m_Stt->setSig(equator, sigE) ;
    m_Stt->setAlpha(2*_tauT_/_M0_*_lambda_*RHO*ALPHA*(_Te_-_Tp_)) ;
    m_Stt->setGamma(2*_tauT_/_M0_*_lambda_*RHO*BETA*(_Se_-_Sp_)) ;
    m_Stt->setDelta(_tauT_/_tauS_) ;
    m_Stt->setTrans(2*_tauT_ / _M0_ * phi) ;
    m_Cst->aim(Te, m_Aim->get(Te)) ;
    m_Cst->aim(Tp, m_Aim->get(Tp)) ;
    m_Cst->aim(Se, m_Aim->get(Se)) ;
    m_Cst->aim(Sp, m_Aim->get(Sp)) ;
    m_Cst->aim(M0, m_Aim->get(M0)) ;
    m_Cst->aim(tauS, m_Aim->get(tauS)) ;
    m_Cst->aim(tauT, m_Aim->get(tauT)) ;
    m_Cst->aim(dt, m_Aim->get(dt)) ;
    m_Cst->aim(lambda, m_Aim->get(lambda)) ;
}
