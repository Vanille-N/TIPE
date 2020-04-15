#include "diagramplot.h"

DiagramPlot::DiagramPlot (QVector<State *> & Stt, QTimer * tick, QWidget * parent) {
    setParent(parent) ;
    cp = new QCustomPlot (this) ;
    m_Stt = Stt ;
    for (int K = 0; K < NB_POINTS; K++) {
        Xhist.push_back(new Circular (HIST_LEN_DIAG)) ;
        Yhist.push_back(new Circular (HIST_LEN_DIAG)) ;
    }
    setup() ;
    connect(tick, SIGNAL(timeout()), this, SLOT(dataSlot())) ;
}

void DiagramPlot::setup () {
    int nbplots = 3 ;
    for (int K = 0; K < NB_POINTS; K++) {
        cp->addGraph() ; // Equilibre
        cp->graph(nbplots*K+0)->setPen(QPen(QColor("#fbc433"))) ;
        cp->graph(nbplots*K+0)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4)) ;
        cp->addGraph() ; // Positions passées
        cp->graph(nbplots*K+1)->setPen(QPen(QColor("#ed8227"))) ;
        cp->graph(nbplots*K+1)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2)) ;
        cp->addGraph() ; // Position actuelle
        cp->graph(nbplots*K+2)->setPen(QPen(QColor("#981526"))) ;
        cp->graph(nbplots*K+2)->setLineStyle(QCPGraph::lsNone) ;
        cp->graph(nbplots*K+2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10)) ;
    }
    cp->xAxis->setLabel("α'");
    cp->yAxis->setLabel("ϕ'");
    cp->replot() ;
}

inline double dPhi (double phi) {
    return (phi >= 0 ? 1 : -1 );
}

inline double sq (double x) {
    return x * x ;
}

inline double Alpha (double phi, double beta, double delta) {
    return (1 + abs(phi)) * (phi + (beta*delta) / (delta + abs(phi))) ;
}

void DiagramPlot::dataSlot () {
    double xmax = -1e10, xmin = 1e10, ymax = -1e10, ymin = 1e10 ;
    int nbplots = 3 ;
    for (int K = 0; K < NB_POINTS; K++) {
        double phimax = std::max(1.0, m_Stt[K]->getPhiAdim()) ;
        double phimin = std::min(-.5, m_Stt[K]->getPhiAdim()) ;
        double beta = m_Stt[K]->getBeta() ;
        double delta = m_Stt[K]->getDelta() ;

        QVector<double> alpha(ALPHA_NB_POINTS), phi(ALPHA_NB_POINTS);
        QVector<double> X(1), Y(1) ;
        for (int i = 0; i<ALPHA_NB_POINTS; ++i) {
            phi[i] = phimin + (phimax-phimin)*i/ALPHA_NB_POINTS ;
        }
        for (int i = 0; i < ALPHA_NB_POINTS; i++) {
            alpha[i] = Alpha(phi[i], beta, delta) ;
        }
        X[0] = m_Stt[K]->getAlpha() ;
        Y[0] = m_Stt[K]->getPhiAdim() ;
        Xhist[K]->insert(X[0]) ;
        Yhist[K]->insert(Y[0]) ;

        cp->graph(nbplots*K+0)->setData(alpha, phi) ;
        cp->graph(nbplots*K+1)->setData(Xhist[K]->extract(), Yhist[K]->extract()) ;
        cp->graph(nbplots*K+2)->setData(X, Y) ;
        xmin = std::min(std::min(alpha[0], beta), xmin) ;
        xmax = std::max(std::max(alpha[ALPHA_NB_POINTS-1], beta), xmax) ;
        ymax = std::max(phi[0], ymax) ;
        ymin = std::min(phi[ALPHA_NB_POINTS-1], ymin) ;
    }

    cp->xAxis->setRange(xmin, xmax) ;
    cp->yAxis->setRange(ymin, ymax) ;
    cp->replot();
}

void DiagramPlot::setFixedSize (int x, int y) {
    cp->setFixedSize(x, y) ;
}
