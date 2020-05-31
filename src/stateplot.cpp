#include "stateplot.h"

/* The StatePlot shows a series of states on a temperature-salinity diagram.
 * Density is shown as a color gradient in the background with a legend on
 * the right.
 */
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
#if LINUX
    cp->setFont(QFont("ubuntu", 11)) ;
#else
    cp->setFont(QFont("arial", 11)) ;
#endif
    setup() ;
}

StatePlot::~StatePlot () {
    //delete m_colorMap ;
    //delete m_colorScale ;
    //delete m_marginGroup ;
    //delete cp ;
    for (int i = 0; i < NB_POINTS; i++) delete Te_hist[i] ;
    for (int i = 0; i < NB_POINTS; i++) delete Tp_hist[i] ;
    for (int i = 0; i < NB_POINTS; i++) delete Se_hist[i] ;
    for (int i = 0; i < NB_POINTS; i++) delete Sp_hist[i] ;
    for (int i = 0; i < NB_POINTS; i++) delete eqTe_hist[i] ;
    for (int i = 0; i < NB_POINTS; i++) delete eqTp_hist[i] ;
    for (int i = 0; i < NB_POINTS; i++) delete eqSe_hist[i] ;
    for (int i = 0; i < NB_POINTS; i++) delete eqSp_hist[i] ;
}

void StatePlot::setup() {
    cp->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom) ;
    cp->axisRect()->setupFullAxesBox(true) ;
    cp->xAxis->setLabel("Température (⁰C)") ;
    cp->yAxis->setLabel("Salinité (psu)") ;

    m_colorMap = new QCPColorMap (cp->xAxis, cp->yAxis) ;
    int nx = 200 ;
    int ny = 200 ;
    m_colorMap->data()->setSize(nx, ny) ;
    m_colorMap->data()->setRange(QCPRange(0, 40), QCPRange(30, 40)) ;
    double S, T, sig ;
    for (int xIndex = 0; xIndex < nx; xIndex++) {
        for (int yIndex=0; yIndex<ny; ++yIndex) {
            m_colorMap->data()->cellToCoord(xIndex, yIndex, &T, &S);
            sig = sigma(S, T) ;
            m_colorMap->data()->setCell(xIndex, yIndex, sig);
        }
    }

    m_colorScale = new QCPColorScale (cp) ;
    cp->plotLayout()->addElement(0, 1, m_colorScale) ;
    m_colorScale->setType(QCPAxis::atRight) ;
    m_colorMap->setColorScale(m_colorScale) ;
    m_colorScale->axis()->setLabel("σ = ρ - ρ₀ (kg⋅m⁻³)") ;

    m_colorMap->setGradient(QCPColorGradient::gpCold) ;
    m_colorMap->rescaleDataRange() ;

    m_marginGroup = new QCPMarginGroup(cp) ;
    cp->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, m_marginGroup) ;
    m_colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, m_marginGroup) ;

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
