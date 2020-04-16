#include "consteditor.h"

ConstEditor::ConstEditor(Const * Aim, cst c, QString param, QWidget * parent) {
    move(0, 800) ;
    m_Aim = Aim ;
    m_c = c ;
    m_parent = parent ;
    m_param = param ;

    m_vbox = new QVBoxLayout ;

    m_lcd = new QLCDNumber(this) ;
    m_lcd->setDigitCount(8) ;
    m_lcd->setSmallDecimalPoint(true) ;
    m_lcd->display(m_Aim->get(m_c)) ;
    m_lcd->setStyleSheet("background-color: black;") ;

    m_buttons = new QGridLayout ;
    m_upOne = new QPushButton("↑", this) ;
    m_upTth = new QPushButton("↑", this) ;
    m_upHth = new QPushButton("↑", this) ;
    m_dnOne = new QPushButton("↓", this) ;
    m_dnTth = new QPushButton("↓", this) ;
    m_dnHth = new QPushButton("↓", this) ;
    m_upOne->setToolTip("+1") ;
    m_upTth->setToolTip("+0.1") ;
    m_upHth->setToolTip("+0.01") ;
    m_dnOne->setToolTip("-1") ;
    m_dnTth->setToolTip("-0.1") ;
    m_dnHth->setToolTip("-0.01") ;
    connect(m_upOne, SIGNAL(clicked()), this, SLOT(incrOne())) ;
    connect(m_upTth, SIGNAL(clicked()), this, SLOT(incrTth())) ;
    connect(m_upHth, SIGNAL(clicked()), this, SLOT(incrHth())) ;
    connect(m_dnOne, SIGNAL(clicked()), this, SLOT(decrOne())) ;
    connect(m_dnTth, SIGNAL(clicked()), this, SLOT(decrTth())) ;
    connect(m_dnHth, SIGNAL(clicked()), this, SLOT(decrHth())) ;
    m_buttons->addWidget(m_upOne, 0, 0) ;
    m_buttons->addWidget(m_upTth, 0, 1) ;
    m_buttons->addWidget(m_upHth, 0, 2) ;
    m_buttons->addWidget(m_dnOne, 1, 0) ;
    m_buttons->addWidget(m_dnTth, 1, 1) ;
    m_buttons->addWidget(m_dnHth, 1, 2) ;

    switch (m_c) {
        case Te:
        case Tp: setStyleSheet("background-color: lightblue;") ; break ;
        case Se:
        case Sp: setStyleSheet("background-color: lightgreen;") ; break ;
        case dt:
        case tauS:
        case tauT: setStyleSheet("background-color: pink;") ; break ;
        case lambda:
        case M0: setStyleSheet("background-color: orange;") ; break ;
    }

    m_okButton = new QPushButton("OK", this) ;
    connect(m_okButton, SIGNAL(clicked()), m_parent, SLOT(delEd())) ;

    m_vbox->addWidget(new QLabel("Editor for "+m_param)) ;
    m_vbox->addWidget(m_lcd) ;
    m_vbox->addLayout(m_buttons) ;
    m_vbox->addWidget(m_okButton) ;
    setLayout(m_vbox) ;
}

void ConstEditor::incrOne () {
    chval(1.0) ;
}

void ConstEditor::incrTth () {
    chval(0.1) ;
}

void ConstEditor::incrHth () {
    chval(0.01) ;
}

void ConstEditor::decrOne () {
    chval(-1.0) ;
}

void ConstEditor::decrTth () {
    chval(-0.1) ;
}

void ConstEditor::decrHth () {
    chval(-0.01) ;
}

void ConstEditor::chval (double step) {
    double oom = m_Aim->orderOfMagnitude(m_c) ;
    double curr = m_Aim->get(m_c) ;
    if ((curr + oom*step)/curr < 0.001) {
        oom /= 10 ;
    }
    m_Aim->set(m_c, oom*step + m_Aim->get(m_c)) ;
    m_lcd->display(m_Aim->get(m_c)) ;
}

void ConstEditor::refresh () {
    m_lcd->display(m_Aim->get(m_c)) ;
}
