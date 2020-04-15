#include "constdisplayer.h"

ConstDisplayer::ConstDisplayer (QString label, QWidget * parent, Const * Cst, Const * Aim, cst c, QString legend) {
    setFixedSize(70, 70) ;
    m_parent = parent ;
    m_Cst = Cst ;
    m_Aim = Aim ;
    m_c = c ;
    m_label = label ;
    setToolTip(legend) ;
    connect(m_parent, SIGNAL(refresh()), this, SLOT(refresh())) ;
    m_ed = new ConstEditor(m_Aim, m_c, m_label, this) ;
    connect(m_parent, SIGNAL(refresh()), m_ed, SLOT(refresh())) ;
    m_vbox = new QVBoxLayout ;
    setParent(m_parent) ;
    m_lcd = new QLCDNumber() ;
    m_lcd->setSmallDecimalPoint(true) ;
    m_lcd->setDigitCount(7) ;
    m_lcd->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcd->setAutoFillBackground(true) ;
    QPalette Pal = m_lcd->palette() ;
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::black) ;
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::white) ;
    m_lcd->setPalette(Pal) ;
    m_lcd->display(m_Cst->get(m_c)) ;

    m_varname = new QLabel(m_label) ;
    m_varname->setAlignment(Qt::AlignCenter) ;
    m_varname->setFont(QFont("ubuntu", 15)) ;

    m_vbox->addWidget(m_lcd) ;
    m_vbox->addWidget(m_varname) ;

    setLayout(m_vbox) ;

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

    connect(this, SIGNAL(clicked()), this, SLOT(launchEditor())) ;
    connect(m_parent, SIGNAL(closed()), m_ed, SLOT(close())) ;
}

void ConstDisplayer::refresh () {
    m_lcd->display(m_Cst->get(m_c)) ;
}

void ConstDisplayer::launchEditor () {
    m_ed->close() ;
    m_ed->show() ;
}

void ConstDisplayer::delEd () {
    m_ed->close() ;
    m_lcd->display(m_Cst->get(m_c)) ;
}
