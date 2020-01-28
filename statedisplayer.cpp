#include "statedisplayer.h"

StateDisplayer::StateDisplayer (QString label, QWidget * parent, State * Stt, loc l) {
    setFixedSize(200, 400) ;
    m_parent = parent ;
    m_Stt = Stt ;
    m_l = l ;
    m_label = "<html><strong>" + label + "</strong></html>" ;
    m_ed = new StateEditor(m_Stt, m_l, m_label, this) ;
    m_vbox = new QVBoxLayout ;
    connect(m_parent, SIGNAL(refresh()), this, SLOT(refresh())) ;
    connect(m_parent, SIGNAL(refresh()), m_ed, SLOT(refresh())) ;
    setParent(m_parent) ;
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
    m_lcdSig->setToolTip("Densité (normalisée)") ;
    m_lcdS->setToolTip("Salinité") ;
    m_lcdT->setToolTip("Température") ;
    QPalette Pal = m_lcdS->palette() ;
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::black) ;
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::white) ;
    m_lcdS->setPalette(Pal) ;
    m_lcdT->setPalette(Pal) ;

    m_lcdS->display(m_Stt->getS(m_l)) ;
    m_lcdT->display(m_Stt->getT(m_l)) ;
    m_lcdSig->display(m_Stt->getSig(m_l)) ;

    m_varname = new QLabel(m_label) ;
    m_varname->setAlignment(Qt::AlignCenter) ;
    m_varname->setFont(QFont("helvetica", 20)) ;

    m_vbox->addWidget(m_varname) ;
    m_SigLabel = new QLabel ("σ") ;
    m_SLabel = new QLabel ("S") ;
    m_TLabel = new QLabel ("T") ;
    m_SigLabel->setAlignment(Qt::AlignCenter) ;
    m_SLabel->setAlignment(Qt::AlignCenter) ;
    m_TLabel->setAlignment(Qt::AlignCenter) ;
    m_SigLabel->setFont(QFont("helvetica", 15)) ;
    m_SLabel->setFont(QFont("helvetica", 15)) ;
    m_TLabel->setFont(QFont("helvetica", 15)) ;
    m_vbox->addWidget(m_SigLabel) ;
    m_vbox->addWidget(m_lcdSig) ;
    m_vbox->addWidget(m_SLabel) ;
    m_vbox->addWidget(m_lcdS) ;
    m_vbox->addWidget(m_TLabel) ;
    m_vbox->addWidget(m_lcdT) ;

    setLayout(m_vbox) ;

    connect(this, SIGNAL(clicked()), this, SLOT(launchEditor())) ;
}

void StateDisplayer::refresh () {
    m_lcdSig->display(m_Stt->getSig(m_l)) ;
    m_lcdS->display(m_Stt->getS(m_l)) ;
    m_lcdT->display(m_Stt->getT(m_l)) ;
}

void StateDisplayer::launchEditor () {
    m_ed->show() ;
}

void StateDisplayer::delEd () {
    m_lcdSig->display(m_Stt->getSig(m_l)) ;
    m_lcdS->display(m_Stt->getS(m_l)) ;
    m_lcdT->display(m_Stt->getT(m_l)) ;
    m_ed->close() ;
}
