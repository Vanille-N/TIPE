#include "plotwindow.h"
#include "ui_plotwindow.h"
//#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

PlotWindow::PlotWindow (State * Stt, QTimer * tick) : QMainWindow (nullptr), ui(new Ui::PlotWindow) {
  ui->setupUi(this);
  setGeometry(700, 250, 600, 400) ;
  m_Stt = Stt ;
  setupDemo() ;
  connect(tick, SIGNAL(timeout()), this, SLOT(thermohalineDataSlot())) ;
}

void PlotWindow::setupDemo() {
  setupThermoHaline(ui->customPlot) ;
  setWindowTitle("Diagramme Flux-Forçage") ;
  statusBar()->clearMessage() ;
  ui->customPlot->replot() ;
}

void PlotWindow::setupThermoHaline(QCustomPlot *customPlot) {
    customPlot->addGraph() ; // Equilibre
    customPlot->graph(0)->setPen(QPen(QColor(162, 252, 251))) ; // Bleu
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone) ;
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5)) ;
    customPlot->addGraph() ; // Position actuelle
    customPlot->graph(1)->setPen(QPen(QColor(255, 58, 23))) ; // Rouge-orange
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone) ;
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10)) ;
}

inline double dPhi (double phi) {
    return (phi >= 0 ? 1 : -1 );
}

inline double sq (double x) {
    return x*x ;
}

inline double dAlpha (double phi, double gamma, double delta) {
    return (phi + delta*gamma/(delta + std::abs(phi))) * dPhi(phi)
         + (1 + std::abs(phi)) * (1 - (gamma*delta)/(sq(delta + std::abs(phi))) * dPhi(phi)) ;
}

void PlotWindow::thermohalineDataSlot () {
    double phirng = 1.0 ;
    double gamma = m_Stt->getGamma() ;
    double delta = m_Stt->getDelta() ;

    QVector<double> alpha(301), phi(301);
    QVector<double> X(1), Y(1) ;
    for (int i=0; i<301; ++i) {
        phi[i] = (i/150.0 - 1) * phirng ;
        //printf("%d:%f ", i, phi[i]) ;
    }
    double dphi = phi[151] - phi[150] ;
    alpha[150] = gamma ;
    for (int i = 151; i < 301; i++) {
        alpha[i] = alpha[i-1] + dAlpha(phi[i-1], gamma, delta) * dphi ;
    }
    for (int i = 149; i >= 0; i--) {
        alpha[i] = alpha[i+1] - dAlpha(phi[i+1], gamma, delta) * dphi ;
    }
    X[0] = m_Stt->getAlpha() ;
    Y[0] = m_Stt->getTrans() ;

    // create graph and assign data to it:
    ui->customPlot->graph(0)->setData(alpha, phi) ;
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("alpha");
    ui->customPlot->yAxis->setLabel("phi");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(alpha[0], alpha[alpha.size()-1]) ;
    ui->customPlot->yAxis->setRange(phi[0], phi[phi.size()-1]) ;

    ui->customPlot->graph(1)->setData(X, Y) ;

    ui->customPlot->replot();
}

PlotWindow::~PlotWindow() {
  delete ui;
}
