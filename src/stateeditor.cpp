#include "stateeditor.h"

StateEditor::StateEditor(QVector<State *> & Stt, loc l, QString param, QWidget * parent) {
    m_Stt = Stt ;
    m_l = l ;
    m_parent = parent ;
    m_param = param ;

    m_vbox = new QVBoxLayout ;
    m_hbox = new QHBoxLayout ;

    m_Sbox = new QVBoxLayout ;
    m_lcdS = new QLCDNumber(this) ;
    m_lcdS->setStyleSheet("background-color: black;") ;
    m_lcdS->setSmallDecimalPoint(true) ;
    m_lcdS->setDigitCount(8) ;
    m_lcdS->display(m_Stt[0]->getS(m_l)) ;
    m_buttonsS = new QGridLayout ;
    m_upOneS = new QPushButton("↑", this) ;
    m_upTthS = new QPushButton("↑", this) ;
    m_upHthS = new QPushButton("↑", this) ;
    m_dnOneS = new QPushButton("↓", this) ;
    m_dnTthS = new QPushButton("↓", this) ;
    m_dnHthS = new QPushButton("↓", this) ;
    m_upOneS->setToolTip("+1") ;
    m_upTthS->setToolTip("+0.1") ;
    m_upHthS->setToolTip("+0.01") ;
    m_dnOneS->setToolTip("-1") ;
    m_dnTthS->setToolTip("-0.1") ;
    m_dnHthS->setToolTip("-0.01") ;
    connect(m_upOneS, SIGNAL(clicked()), this, SLOT(incrOneS())) ;
    connect(m_upTthS, SIGNAL(clicked()), this, SLOT(incrTthS())) ;
    connect(m_upHthS, SIGNAL(clicked()), this, SLOT(incrHthS())) ;
    connect(m_dnOneS, SIGNAL(clicked()), this, SLOT(decrOneS())) ;
    connect(m_dnTthS, SIGNAL(clicked()), this, SLOT(decrTthS())) ;
    connect(m_dnHthS, SIGNAL(clicked()), this, SLOT(decrHthS())) ;
    m_buttonsS->addWidget(m_upOneS, 0, 0) ;
    m_buttonsS->addWidget(m_upTthS, 0, 1) ;
    m_buttonsS->addWidget(m_upHthS, 0, 2) ;
    m_buttonsS->addWidget(m_dnOneS, 1, 0) ;
    m_buttonsS->addWidget(m_dnTthS, 1, 1) ;
    m_buttonsS->addWidget(m_dnHthS, 1, 2) ;
    m_Sbox->addWidget(new QLabel ("Salinity")) ;
    m_Sbox->addWidget(m_lcdS) ;
    m_Sbox->addLayout(m_buttonsS) ;

    m_Tbox = new QVBoxLayout ;
    m_lcdT = new QLCDNumber(this) ;
    m_lcdT->setStyleSheet("background-color: black;") ;
    m_lcdT->setSmallDecimalPoint(true) ;
    m_lcdT->setDigitCount(8) ;
    m_lcdT->display(m_Stt[0]->getT(m_l)) ;
    m_buttonsT = new QGridLayout ;
    m_upOneT = new QPushButton("↑", this) ;
    m_upTthT = new QPushButton("↑", this) ;
    m_upHthT = new QPushButton("↑", this) ;
    m_dnOneT = new QPushButton("↓", this) ;
    m_dnTthT = new QPushButton("↓", this) ;
    m_dnHthT = new QPushButton("↓", this) ;
    m_upOneT->setToolTip("+1") ;
    m_upTthT->setToolTip("+0.1") ;
    m_upHthT->setToolTip("+0.01") ;
    m_dnOneT->setToolTip("-1") ;
    m_dnTthT->setToolTip("-0.1") ;
    m_dnHthT->setToolTip("-0.01") ;
    connect(m_upOneT, SIGNAL(clicked()), this, SLOT(incrOneT())) ;
    connect(m_upTthT, SIGNAL(clicked()), this, SLOT(incrTthT())) ;
    connect(m_upHthT, SIGNAL(clicked()), this, SLOT(incrHthT())) ;
    connect(m_dnOneT, SIGNAL(clicked()), this, SLOT(decrOneT())) ;
    connect(m_dnTthT, SIGNAL(clicked()), this, SLOT(decrTthT())) ;
    connect(m_dnHthT, SIGNAL(clicked()), this, SLOT(decrHthT())) ;
    m_buttonsT->addWidget(m_upOneT, 0, 0) ;
    m_buttonsT->addWidget(m_upTthT, 0, 1) ;
    m_buttonsT->addWidget(m_upHthT, 0, 2) ;
    m_buttonsT->addWidget(m_dnOneT, 1, 0) ;
    m_buttonsT->addWidget(m_dnTthT, 1, 1) ;
    m_buttonsT->addWidget(m_dnHthT, 1, 2) ;
    m_Tbox->addWidget(new QLabel ("Temperature")) ;
    m_Tbox->addWidget(m_lcdT) ;
    m_Tbox->addLayout(m_buttonsT) ;


    m_okButton = new QPushButton("OK", this) ;
    connect(m_okButton, SIGNAL(clicked()), m_parent, SLOT(delEd())) ;
    m_vbox->addWidget(new QLabel("Editor for "+m_param)) ;
    m_hbox->addLayout(m_Sbox) ;
    m_hbox->addLayout(m_Tbox) ;
    m_vbox->addLayout(m_hbox) ;
    m_vbox->addWidget(m_okButton) ;
    setLayout(m_vbox) ;
}

void StateEditor::incrOneS () { chvalS(1.0) ; }
void StateEditor::incrTthS () { chvalS(0.1) ; }
void StateEditor::incrHthS () { chvalS(0.01) ; }
void StateEditor::decrOneS () { chvalS(-1.0) ; }
void StateEditor::decrTthS () { chvalS(-0.1) ; }
void StateEditor::decrHthS () { chvalS(-0.01) ; }

void StateEditor::chvalS (double step) {
    m_Stt[0]->setS(m_l, step + m_Stt[0]->getS(m_l)) ;
    m_lcdS->display(m_Stt[0]->getS(m_l)) ;
    for (int K = 1; K < NB_POINTS; K++) {
        m_Stt[K]->setS(m_l, m_Stt[0]->getS((m_l))) ;
    }
}

void StateEditor::incrOneT () { chvalT(1.0) ; }
void StateEditor::incrTthT () { chvalT(0.1) ; }
void StateEditor::incrHthT () { chvalT(0.01) ; }
void StateEditor::decrOneT () { chvalT(-1.0) ; }
void StateEditor::decrTthT () { chvalT(-0.1) ; }
void StateEditor::decrHthT () { chvalT(-0.01) ; }

void StateEditor::chvalT (double step) {
    m_Stt[0]->setT(m_l, step + m_Stt[0]->getT(m_l)) ;
    m_lcdT->display(m_Stt[0]->getT(m_l)) ;
    for (int K = 1; K < NB_POINTS; K++) {
        m_Stt[K]->setT(m_l, m_Stt[0]->getT((m_l))) ;
    }
}

void StateEditor::refresh () {
    m_lcdS->display(m_Stt[0]->getS(m_l)) ;
    m_lcdT->display(m_Stt[0]->getT(m_l)) ;
}
