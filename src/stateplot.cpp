#include "stateplot.h"

StatePlot::StatePlot (QVector<State *> & Stt, QVector<Const *> & Cst, QWidget * parent) {
    setParent(parent) ;
    m_Stt = Stt ;
    m_Cst = Cst ;
    for (int K = 0; K < NB_POINTS; K++) {
        Te_hist.push_back(new Circular (HIST_LEN_STATE)) ;
        Tp_hist.push_back(new Circular (HIST_LEN_STATE)) ;
        Se_hist.push_back(new Circular (HIST_LEN_STATE)) ;
        Sp_hist.push_back(new Circular (HIST_LEN_STATE)) ;
        eqTe_hist.push_back(new Circular (HIST_LEN_STATE)) ;
        eqTp_hist.push_back(new Circular (HIST_LEN_STATE)) ;
        eqSe_hist.push_back(new Circular (HIST_LEN_STATE)) ;
        eqSp_hist.push_back(new Circular (HIST_LEN_STATE)) ;
    }
    cp = new QCustomPlot (this) ;
    cp->setFont(QFont("ubuntu", 11)) ;
    setup() ;
}

void StatePlot::setup() {
    cp->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom) ;
    cp->axisRect()->setupFullAxesBox(true) ;
    cp->xAxis->setLabel("Température (⁰C)") ;
    cp->yAxis->setLabel("Salinité (psu)") ;

    QCPColorMap * colorMap = new QCPColorMap (cp->xAxis, cp->yAxis) ;
    int nx = 200 ;
    int ny = 200 ;
    colorMap->data()->setSize(nx, ny) ;
    colorMap->data()->setRange(QCPRange(0, 40), QCPRange(30, 40)) ;
    double S, T, sig ;
    for (int xIndex = 0; xIndex < nx; xIndex++) {
        for (int yIndex=0; yIndex<ny; ++yIndex) {
            colorMap->data()->cellToCoord(xIndex, yIndex, &T, &S);
            sig = sigma(S, T) ;
            colorMap->data()->setCell(xIndex, yIndex, sig);
        }
    }

    QCPColorScale * colorScale = new QCPColorScale (cp) ;
    cp->plotLayout()->addElement(0, 1, colorScale) ;
    colorScale->setType(QCPAxis::atRight) ;
    colorMap->setColorScale(colorScale) ;
    colorScale->axis()->setLabel("σ = ρ - ρ₀ (kg⋅m⁻³)") ;

    colorMap->setGradient(QCPColorGradient::gpCold) ;
    colorMap->rescaleDataRange() ;

    QCPMarginGroup * marginGroup = new QCPMarginGroup(cp) ;
    cp->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup) ;
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup) ;

    cp->rescaleAxes() ;
    int nbplots = 8 ;
    for (int K = 0; K < NB_POINTS; K++) {
        cp->addGraph() ; // Equilibre pole historique
        cp->graph(nbplots*K+0)->setPen(QPen(QColor("#33a501"))) ;
        cp->graph(nbplots*K+0)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1)) ;
        cp->addGraph() ; // Equilibre équateur historique
        cp->graph(nbplots*K+1)->setPen(QPen(QColor("#e0301e"))) ;
        cp->graph(nbplots*K+1)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1)) ;
        cp->addGraph() ; // Pole historique
        cp->graph(nbplots*K+2)->setPen(QPen(QColor("#38d807"))) ;
        cp->graph(nbplots*K+2)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1)) ;
        cp->addGraph() ; // Equateur historique
        cp->graph(nbplots*K+3)->setPen(QPen(QColor("#eb8c00"))) ;
        cp->graph(nbplots*K+3)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1)) ;
        cp->addGraph() ; // Equilibre pole actuel
        cp->graph(nbplots*K+4)->setPen(QPen(QColor("#33a501"))) ;
        cp->graph(nbplots*K+4)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10)) ;
        cp->addGraph() ; // Equilibre equateur actuel
        cp->graph(nbplots*K+5)->setPen(QPen(QColor("#e0301e"))) ;
        cp->graph(nbplots*K+5)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+5)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10)) ;
        cp->addGraph() ; // Pole actuel
        cp->graph(nbplots*K+6)->setPen(QPen(QColor("#38d807"))) ;
        cp->graph(nbplots*K+6)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+6)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10)) ;
        cp->addGraph() ; // Equateur actuel
        cp->graph(nbplots*K+7)->setPen(QPen(QColor("#eb8c00"))) ;
        cp->graph(nbplots*K+7)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+7)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10)) ;
        cp->replot() ;
    }
}

//inline double dPhi (double phi) {
//    return (phi >= 0 ? 1 : -1 );
//}

//inline double sq (double x) {
//    return x*x ;
//}

//inline double dAlpha (double phi, double beta, double delta) {
//    return (phi + delta*beta/(delta + std::abs(phi))) * dPhi(phi)
//         + (1 + std::abs(phi)) * (1 - (beta*delta)/(sq(delta + std::abs(phi))) * dPhi(phi)) ;
//}

//double itermin (QList<QVector<double>> iter) {
//    double m = 1e100 ;
//    foreach (QVector<double> vec, iter) {
//        for (int i = vec.size()-1; i >= 0; i--) {
//            m = std::min(vec[i], m) ;
//        }

//    }
//    return m ;
//}

//double itermax (QList<QVector<double>> iter) {
//    double m = -1e100 ;
//    foreach (QVector<double> vec, iter) {
//        for (int i = vec.size()-1; i >= 0; i--) {
//            m = std::max(vec[i], m) ;
//        }
//    }
//    return m ;
//}

void StatePlot::dataSlot () {
    for (int K = 0; K < NB_POINTS; K++) {
        QVector<double> Tcurr_e (1) ;
        QVector<double> Scurr_e (1) ;
        QVector<double> Tcurr_p (1) ;
        QVector<double> Scurr_p (1) ;
        QVector<double> eqTcurr_e (1) ;
        QVector<double> eqScurr_e (1) ;
        QVector<double> eqTcurr_p (1) ;
        QVector<double> eqScurr_p (1) ;
        Tcurr_e[0] = m_Stt[K]->getT(equator) ;
        Scurr_e[0] = m_Stt[K]->getS(equator) ;
        Tcurr_p[0] = m_Stt[K]->getT(pole) ;
        Scurr_p[0] = m_Stt[K]->getS(pole) ;
        eqTcurr_e[0] = m_Cst[K]->get(Te) ;
        eqScurr_e[0] = m_Cst[K]->get(Se) ;
        eqTcurr_p[0] = m_Cst[K]->get(Tp) ;
        eqScurr_p[0] = m_Cst[K]->get(Sp) ;
        Te_hist[K]->insert(Tcurr_e[0]) ;
        Tp_hist[K]->insert(Tcurr_p[0]) ;
        Se_hist[K]->insert(Scurr_e[0]) ;
        Sp_hist[K]->insert(Scurr_p[0]) ;
        eqTe_hist[K]->insert(eqTcurr_e[0]) ;
        eqTp_hist[K]->insert(eqTcurr_p[0]) ;
        eqSe_hist[K]->insert(eqScurr_e[0]) ;
        eqSp_hist[K]->insert(eqScurr_p[0]) ;
        auto _Te = Te_hist[K]->extract() ;
        auto _Tp = Tp_hist[K]->extract() ;
        auto _Se = Se_hist[K]->extract() ;
        auto _Sp = Sp_hist[K]->extract() ;
        auto _eqTe = eqTe_hist[K]->extract() ;
        auto _eqTp = eqTp_hist[K]->extract() ;
        auto _eqSe = eqSe_hist[K]->extract() ;
        auto _eqSp = eqSp_hist[K]->extract() ;

        int nbplots = 8 ;
        cp->graph(nbplots*K+0)->setData(_eqTp, _eqSp) ;
        cp->graph(nbplots*K+1)->setData(_eqTe, _eqSe) ;
        cp->graph(nbplots*K+2)->setData(_Tp, _Sp) ;
        cp->graph(nbplots*K+3)->setData(_Te, _Se) ;
        cp->graph(nbplots*K+4)->setData(eqTcurr_p, eqScurr_p) ;
        cp->graph(nbplots*K+5)->setData(eqTcurr_e, eqScurr_e) ;
        cp->graph(nbplots*K+6)->setData(Tcurr_p, Scurr_p) ;
        cp->graph(nbplots*K+7)->setData(Tcurr_e, Scurr_e) ;
    }
    cp->replot() ;
}

void StatePlot::setFixedSize (int x, int y) {
    cp->setFixedSize(x, y) ;
}