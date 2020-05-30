#include "constdisplayer.h"

/* One of the colored buttons with the name of a constant and a lcd display.
 * It is responsible for bridging the gap between one of Const's fields and
 * an associated ConstEditor.
 */
ConstDisplayer::ConstDisplayer (QString label, QWidget * parent, Const * Cst, Const * Aim, cst c, QString legend) {
    setFixedSize(70, 70) ;
    m_Cst = Cst ;
    m_Aim = Aim ;
    m_c = c ;
    m_label = label ;
    setToolTip(legend) ;
    connect(parent, SIGNAL(refresh()), this, SLOT(refresh())) ;
    m_ed = new ConstEditor(m_Aim, m_c, m_label, this) ;
    connect(parent, SIGNAL(refresh()), m_ed, SLOT(refresh())) ;
    m_vbox = new QVBoxLayout ;
    setParent(parent) ;
    m_lcd = new QLCDNumber (this) ;
    m_lcd->setSmallDecimalPoint(true) ;
    m_lcd->setDigitCount(7) ;
    m_lcd->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcd->setAutoFillBackground(true) ;
    QPalette Pal = m_lcd->palette() ;
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::black) ;
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::white) ;
    m_lcd->setPalette(Pal) ;
    m_lcd->display(m_Cst->get(m_c)) ;

    m_varname = new QLabel(m_label, this) ;
    m_varname->setAlignment(Qt::AlignCenter) ;
#if LINUX
    m_varname->setFont(QFont("ubuntu", 15)) ;
#else
    m_varname->setFont(QFont("arial", 13)) ;
#endif

    m_vbox->addWidget(m_lcd) ;
    m_vbox->addWidget(m_varname) ;

    setLayout(m_vbox) ;

    switch (m_c) {
        case Te: case Tp:
            setStyleSheet("background-color: lightblue;") ; break ;
        case Se: case Sp:
            setStyleSheet("background-color: lightgreen;") ; break ;
        case dt: case tauS: case tauT:
            setStyleSheet("background-color: pink;") ; break ;
        case lambda: case M0:
            setStyleSheet("background-color: orange;") ; break ;
    }

    connect(this, SIGNAL(clicked()), this, SLOT(launchEditor())) ;
    connect(parent, SIGNAL(closed()), m_ed, SLOT(close())) ;
}

ConstDisplayer::~ConstDisplayer () {
    delete m_ed ;
}

void ConstDisplayer::refresh () {
    m_lcd->display(m_Cst->get(m_c)) ;
}

void ConstDisplayer::launchEditor () {
    m_ed->close() ;
    move(0, 800) ;
    m_ed->show() ;
}

/* In reality, doesn't delete the editor, just closes it
 */
void ConstDisplayer::delEd () {
    m_ed->close() ;
    m_lcd->display(m_Cst->get(m_c)) ;
}
