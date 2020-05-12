#include "statedisplayer.h"

StateDisplayer::StateDisplayer (QString label, QWidget * parent, QVector<State *> & Stt, loc l) {
    setFixedSize(150, 350) ;
    m_Stt = Stt ;
    m_l = l ;
    m_label = "<html><strong>" + label + "</strong></html>" ;
    m_ed = new StateEditor(m_Stt, m_l, m_label, this) ;
    m_vbox = new QVBoxLayout ;
    connect(parent, SIGNAL(refresh()), this, SLOT(refresh())) ;
    connect(parent, SIGNAL(refresh()), m_ed, SLOT(refresh())) ;
    setParent(parent) ;
    m_lcdSig = new QLCDNumber() ;
    m_lcdS = new QLCDNumber() ;
    m_lcdT = new QLCDNumber() ;
    m_lcdSig->setSmallDecimalPoint(true) ;
    m_lcdS->setSmallDecimalPoint(true) ;
    m_lcdT->setSmallDecimalPoint(true) ;
    m_lcdSig->setDigitCount(7) ;
    m_lcdS->setDigitCount(7) ;
    m_lcdT->setDigitCount(7) ;
    m_lcdSig->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcdS->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcdT->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcdSig->setAutoFillBackground(true) ;
    m_lcdS->setAutoFillBackground(true) ;
    m_lcdT->setAutoFillBackground(true) ;
    m_lcdSig->setToolTip("Masse volumique (normalisée), kg⋅m⁻³") ;
    m_lcdS->setToolTip("Salinité, psu") ;
    m_lcdT->setToolTip("Température, °C") ;
    QPalette Pal = m_lcdS->palette() ;
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::black) ;
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::white) ;
    m_lcdS->setPalette(Pal) ;
    m_lcdT->setPalette(Pal) ;

    m_lcdS->display(m_Stt[0]->getS(m_l)) ;
    m_lcdT->display(m_Stt[0]->getT(m_l)) ;
    m_lcdSig->display(m_Stt[0]->getSig(m_l)) ;

    m_varname = new QLabel(m_label) ;
    m_varname->setAlignment(Qt::AlignCenter) ;
    m_varname->setFont(QFont("ubuntu", 20)) ;

    m_vbox->addWidget(m_varname) ;
    m_SigLabel = new QLabel ("σ") ;
    m_SLabel = new QLabel ("S") ;
    m_TLabel = new QLabel ("T") ;
    m_SigLabel->setAlignment(Qt::AlignCenter) ;
    m_SLabel->setAlignment(Qt::AlignCenter) ;
    m_TLabel->setAlignment(Qt::AlignCenter) ;
    m_SigLabel->setFont(QFont("ubuntu", 15)) ;
    m_SLabel->setFont(QFont("ubuntu", 15)) ;
    m_TLabel->setFont(QFont("ubuntu", 15)) ;
    m_vbox->addWidget(m_SigLabel) ;
    m_vbox->addWidget(m_lcdSig) ;
    m_vbox->addWidget(m_SLabel) ;
    m_vbox->addWidget(m_lcdS) ;
    m_vbox->addWidget(m_TLabel) ;
    m_vbox->addWidget(m_lcdT) ;

    setLayout(m_vbox) ;

    connect(this, SIGNAL(clicked()), this, SLOT(launchEditor())) ;
    connect(parent, SIGNAL(closed()), m_ed, SLOT(close())) ;
}

StateDisplayer::~StateDisplayer () {
    delete m_ed ;
}

void StateDisplayer::refresh () {
    m_lcdSig->display(m_Stt[0]->getSig(m_l)) ;
    m_lcdS->display(m_Stt[0]->getS(m_l)) ;
    m_lcdT->display(m_Stt[0]->getT(m_l)) ;
}

void StateDisplayer::launchEditor () {
    m_ed->close() ;
    m_ed->show() ;
}

void StateDisplayer::delEd () {
    m_lcdSig->display(m_Stt[0]->getSig(m_l)) ;
    m_lcdS->display(m_Stt[0]->getS(m_l)) ;
    m_lcdT->display(m_Stt[0]->getT(m_l)) ;
    m_ed->close() ;
}
