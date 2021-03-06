#include "timemgr.h"

/* The TimeMgr is the visible display of the internal clock of the simulation.
 * It is the single button labeled 'TIME' in the control panel.
 * Note that TimeMgr is _not_ the timer responsible for periodically pinging
 * the other elements.
 */
TimeMgr::TimeMgr (QWidget * parent, Const * Cst) {
    TIME = 0.0 ;
    setFixedSize(70, 70) ;
    m_Cst = Cst ;
    m_vbox = new QVBoxLayout ;
    setParent(parent) ;
    m_lcd = new QLCDNumber() ;
    m_lcd->setSmallDecimalPoint(true) ;
    m_lcd->setDigitCount(7) ;
    m_lcd->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcd->setAutoFillBackground(true) ;
    QPalette Pal = m_lcd->palette() ;
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::black) ;
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::white) ;
    m_lcd->setPalette(Pal) ;

    m_lcd->display(TIME) ;

    m_vbox->addWidget(m_lcd) ;
    m_vbox->addWidget(new QLabel ("TIME")) ;

    setLayout(m_vbox) ;

    setStyleSheet("background-color: pink;") ;
}

void TimeMgr::tick () {
    TIME += m_Cst->get(dt) ;
    m_lcd->display(TIME) ;
}

double TimeMgr::clock () {
    return TIME ;
}
