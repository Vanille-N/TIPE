#include "calculator.h"

/* The object responsible for all important calculations.
 * (i.e. it knows how to integrate the system of differential equations
 * that emerges from the model.
 * This file also contains information on how to calculate water density.
 */

Calculator::Calculator (QWidget * parent, QVector<State *> & Stt, QVector<Const *> & Cst, Const * Aim, bool * pcpl, bool * peqm) {
    m_Stt = Stt ;
    m_Cst = Cst ;
    m_Aim = Aim ;
    CPL = pcpl ;
    EQM = peqm ;
    m_refreshRoot = parent ;
}

/* Advance the whole system by one unit of time
 */
void Calculator::step () {
#if INTEGRATE_PHI == 0
    for (int K = 0; K < NB_POINTS; K++) {
        // Bring all useful variable into scope
        double _Te = m_Stt[K]->getT(equator) ;
        double _Tp = m_Stt[K]->getT(pole) ;
        double _Se = m_Stt[K]->getS(equator) ;
        double _Sp = m_Stt[K]->getS(pole) ;
        double _Te_ = m_Cst[K]->get(Te) ;
        double _Tp_ = m_Cst[K]->get(Tp) ;
        double _Se_ = m_Cst[K]->get(Se) ;
        double _Sp_ = m_Cst[K]->get(Sp) ;
        double _M0_ = m_Cst[K]->get(M0) ;
        double _lambda_ = m_Cst[K]->get(lambda) ;
        double _tauT_ = m_Cst[K]->get(tauT) ;
        double _tauS_ = m_Cst[K]->get(tauS) ;
        double _dt_ = m_Cst[K]->get(dt) ;
        // Calculate densities
        double sigP = sigma(_Sp, _Tp) ;
        double sigE = sigma(_Se, _Te) ;
        // Calculate variations of the relevant quantities
        // Note that CPL and EQM are bool*, so having them as multiplying
        // factors is an easy way to negate certain effects
        double phi = *CPL * _lambda_ * (sigP - sigE) ;
        double dTe = *CPL * (_Tp - _Te) * (abs(phi) / _M0_) + *EQM * (_Te_ - _Te) / _tauT_ ;
        double dTp = *CPL * (_Te - _Tp) * (abs(phi) / _M0_) + *EQM * (_Tp_ - _Tp) / _tauT_ ;
        double dSe = *CPL * (_Sp - _Se) * (abs(phi) / _M0_) + *EQM * (_Se_ - _Se) / _tauS_ ;
        double dSp = *CPL * (_Se - _Sp) * (abs(phi) / _M0_) + *EQM * (_Sp_ - _Sp) / _tauS_ ;
        // Update the state of the simulation
        m_Stt[K]->setPhi(phi) ;
        m_Stt[K]->setS(pole, _Sp + dSp*_dt_) ;
        m_Stt[K]->setS(equator, _Se + dSe*_dt_) ;
        m_Stt[K]->setT(pole, _Tp + dTp*_dt_) ;
        m_Stt[K]->setT(equator, _Te + dTe*_dt_) ;
        m_Stt[K]->setSig(pole, sigP) ;
        m_Stt[K]->setSig(equator, sigE) ;
        m_Stt[K]->setAlpha(2*_tauT_/_M0_*_lambda_*RHO*ALPHA*(_Te_-_Tp_)) ;
        m_Stt[K]->setBeta(2*_tauT_/_M0_*_lambda_*RHO*BETA*(_Se_-_Sp_)) ;
        m_Stt[K]->setDelta(_tauT_/_tauS_) ;
        m_Stt[K]->setTrans(2*_tauT_ / _M0_ * phi) ;
        m_Cst[K]->aim(Te, m_Aim->get(Te)) ;
        m_Cst[K]->aim(Tp, m_Aim->get(Tp)) ;
        m_Cst[K]->aim(Se, m_Aim->get(Se)) ;
        m_Cst[K]->aim(Sp, m_Aim->get(Sp)) ;
        m_Cst[K]->aim(M0, m_Aim->get(M0)) ;
        m_Cst[K]->aim(tauS, m_Aim->get(tauS)) ;
        m_Cst[K]->aim(tauT, m_Aim->get(tauT)) ;
        m_Cst[K]->aim(dt, m_Aim->get(dt)) ;
        m_Cst[K]->aim(lambda, m_Aim->get(lambda)) ;
    }
#elif INTEGRATE_PHI == 1
    for (int K = 0; K < NB_POINTS; K++) {
        // Bring all relevant quantities into scope
        double _Te0 = m_Stt[K]->getT(equator) ;
        double _Tp0 = m_Stt[K]->getT(pole) ;
        double _Se0 = m_Stt[K]->getS(equator) ;
        double _Sp0 = m_Stt[K]->getS(pole) ;
        double _Te_ = m_Cst[K]->get(Te) ;
        double _Tp_ = m_Cst[K]->get(Tp) ;
        double _Se_ = m_Cst[K]->get(Se) ;
        double _Sp_ = m_Cst[K]->get(Sp) ;
        double _M0_ = m_Cst[K]->get(M0) ;
        double _lambda_ = m_Cst[K]->get(lambda) ;
        double _tauT_ = m_Cst[K]->get(tauT) ;
        double _tauS_ = m_Cst[K]->get(tauS) ;
        double _dt_ = m_Cst[K]->get(dt) ;
        // Calculate first approximation of densities
        double sigP0 = sigma(_Sp0, _Tp0) ;
        double sigE0 = sigma(_Se0, _Te0) ;
        // Calculate first approximation of variations
        // Note that CPL and EQM are bool*, so having them as multiplying
        // factors is an easy way to negate certain effects
        double phi0 = *CPL * _lambda_ * (sigP0 - sigE0) ;
        double dTe0 = *CPL * (_Tp0 - _Te0) * (abs(phi0) / _M0_) + *EQM * (_Te_ - _Te0) / _tauT_ ;
        double dTp0 = *CPL * (_Te0 - _Tp0) * (abs(phi0) / _M0_) + *EQM * (_Tp_ - _Tp0) / _tauT_ ;
        double dSe0 = *CPL * (_Sp0 - _Se0) * (abs(phi0) / _M0_) + *EQM * (_Se_ - _Se0) / _tauS_ ;
        double dSp0 = *CPL * (_Se0 - _Sp0) * (abs(phi0) / _M0_) + *EQM * (_Sp_ - _Sp0) / _tauS_ ;
        // Calculate first approximation of the end values of quantities
        double _Te1 = _Te0 + dTe0 ;
        double _Tp1 = _Tp0 + dTp0 ;
        double _Se1 = _Se0 + dSe0 ;
        double _Sp1 = _Sp0 + dSp0 ;
        // Calculate second approximation of the densities
        double sigP1 = sigma(_Sp1, _Tp1) ;
        double sigE1 = sigma(_Se1, _Te1) ;
        // Calculate second approximation of the flow
        double phi1 = *CPL * _lambda_ * (sigP1 - sigE1) ;
        // The actual flow is approximated by the mean of the two previously
        // calculated values, so are all other quantities, ...
        double phi2 = (phi0 + phi1) / 2 ;
        double _Te2 = (_Te0 + _Te1) / 2 ;
        double _Tp2 = (_Tp0 + _Tp1) / 2 ;
        double _Se2 = (_Se0 + _Se1) / 2 ;
        double _Sp2 = (_Sp0 + _Sp1) / 2 ;
        // ...And the same calculations are reiterated with the new
        // better approximation
        double dTe2 = *CPL * (_Tp2 - _Te2) * (abs(phi2) / _M0_) + *EQM * (_Te_ - _Te2) / _tauT_ ;
        double dTp2 = *CPL * (_Te2 - _Tp2) * (abs(phi2) / _M0_) + *EQM * (_Tp_ - _Tp2) / _tauT_ ;
        double dSe2 = *CPL * (_Sp2 - _Se2) * (abs(phi2) / _M0_) + *EQM * (_Se_ - _Se2) / _tauS_ ;
        double dSp2 = *CPL * (_Se2 - _Sp2) * (abs(phi2) / _M0_) + *EQM * (_Sp_ - _Sp2) / _tauS_ ;
        // Final update of the state of the simulation
        m_Stt[K]->setPhi(phi0) ;
        m_Stt[K]->setS(pole, _Sp0 + dSp2*_dt_) ;
        m_Stt[K]->setS(equator, _Se0 + dSe2*_dt_) ;
        m_Stt[K]->setT(pole, _Tp0 + dTp2*_dt_) ;
        m_Stt[K]->setT(equator, _Te0 + dTe2*_dt_) ;
        m_Stt[K]->setSig(pole, sigP0) ;
        m_Stt[K]->setSig(equator, sigE0) ;
        m_Stt[K]->setAlpha(2*_tauT_/_M0_*_lambda_*RHO*ALPHA*(_Te_-_Tp_)) ;
        m_Stt[K]->setBeta(2*_tauT_/_M0_*_lambda_*RHO*BETA*(_Se_-_Sp_)) ;
        m_Stt[K]->setDelta(_tauT_/_tauS_) ;
        m_Stt[K]->setTrans(2*_tauT_ / _M0_ * phi0) ;
        m_Cst[K]->aim(Te, m_Aim->get(Te)) ;
        m_Cst[K]->aim(Tp, m_Aim->get(Tp)) ;
        m_Cst[K]->aim(Se, m_Aim->get(Se)) ;
        m_Cst[K]->aim(Sp, m_Aim->get(Sp)) ;
        m_Cst[K]->aim(M0, m_Aim->get(M0)) ;
        m_Cst[K]->aim(tauS, m_Aim->get(tauS)) ;
        m_Cst[K]->aim(tauT, m_Aim->get(tauT)) ;
        m_Cst[K]->aim(dt, m_Aim->get(dt)) ;
        m_Cst[K]->aim(lambda, m_Aim->get(lambda)) ;
    }
#endif
}




#if SWEOS == 0
// Linear approximation
double sigma (double S, double T) {
    return RHO * (-ALPHA*(T-T0) + BETA*(S-S0)) ;
}

#elif SWEOS == 1
// Polynomial fit
double sq (double x) {
    return x * x ;
}

double cb (double x) {
    return x * x * x ;
}

// voir https://agupubs.onlinelibrary.wiley.com/doi/epdf/10.1029/1998JC900059
double coeffs [7][3] = {
    {-9.20601e-2, 5.07043e-1, -5.43283e-4},
    {5.10768e-2, -3.69119e-3, 6.54837e-4},
    {8.05999e-1, -9.34012e-4, 1.38777e-6},
    {-7.40849e-3, 5.33243e-5, -1.01563e-7},
    {-3.01036e-3, 1.75145e-5, -2.34892e-8},
    {3.32267e-5, -3.25887e-7, 4.98612e-10},
    {3.21931e-5, -1.65849e-7, 2.17612e-10}
} ;

double P = 0.1013 ;
double C [7] = {0, 0, 0, 0, 0, 0, 0} ;


double calc_C (int i) {
    if (C[i] == 0) {
        C[i] = coeffs[i][0] + coeffs[i][1] * P + coeffs[i][2] * sq(P) ;
    }
    return C[i] ;
}


double sigma (double S, double T) {
    return calc_C(0) + calc_C(1)*T + calc_C(2)*S + calc_C(3)*sq(T) + calc_C(4)*S*T + calc_C(5)*cb(T) + calc_C(6)*S*sq(T) ;
} // (kg.m⁻³)
/* sigma = rho - rho_0
 * (rho_0 = 1000 kg.m¯³)
 * DL valable dans les intervalles :
 * -2 < T < 40 (⁰C)
 * 0 < S < 42 (psu)
 * 0 < P < 100 (MPa)
 */

#else


#endif
