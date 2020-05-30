#include "layoutselector.h"

#include <QLabel>

/* The LayoutSelector is the long window that pops up on the right when
 * the 'Layout' button is pressed.
 * It bears many colored buttons with rectangular drawings that represent
 * each possible configuration of the main window. Clicking on a button
 * switches the window to the selected layout.
 * The 'Screenshot' button at the bottom saves an image of the current
 * state of the main window to a user-specified location.
 */

LayoutSelector::LayoutSelector (QWidget * win) {
    move(1220, 20) ;
    setFixedSize(120, 700) ;
    setWindowTitle("Layout") ;
    m_parent = win;

    auto base = new QVBoxLayout (this) ;
    auto lvA = new QHBoxLayout () ;
    auto lvB = new QHBoxLayout () ;
    auto lvC = new QHBoxLayout () ;
    auto lvD = new QHBoxLayout () ;
    auto lvE = new QHBoxLayout () ;
    auto lvF = new QHBoxLayout () ;
    auto qA = new QPushButton () ;
    auto qB = new QPushButton () ;
    auto qC = new QPushButton () ;
    auto qD = new QPushButton () ;
    auto qE = new QPushButton () ;
    auto qF = new QPushButton () ;
    auto lvAa = new QVBoxLayout () ;
    auto lvAb = new QVBoxLayout () ;
    auto lvAa1 = new QGridLayout () ;
    auto lvBa = new QVBoxLayout () ;
    auto lvCa = new QVBoxLayout () ;
    auto rAa1 = new QLabel * [9] ;
    for (int i = 0; i < 9; i++) rAa1[i] = new QLabel ("", this) ;
    auto rAa2 = new QLabel ("") ;
    auto rAb1 = new QLabel ("") ;
    auto rAb2 = new QLabel ("") ;
    auto rBa1 = new QLabel ("") ;
    auto rBa2 = new QLabel ("") ;
    auto rBb = new QLabel ("") ;
    auto rCa1 = new QLabel ("") ;
    auto rCa2 = new QLabel ("") ;
    auto rCb = new QLabel ("") ;
    auto rDa = new QLabel ("") ;
    auto rDb = new QLabel ("") ;
    auto rE = new QLabel ("") ;
    auto rF = new QLabel ("") ;
    auto capture = new QPushButton ("Screenshot", this) ;

    /* The hierarchy is as follows:
     * base --- lvA --- lvAa --- lvAa1 --- rAa1[0]   (red)
     *      |       |        |         |    ...       ...
     *      |       |        |         `-- rAa1[8]   (red)
     *      |       |        `-- rAa2                (grey)
     *      |       `-- lvAb --- rAb1                (blue)
     *      |                `-- rAb2                (orange)
     *      |-- lvB --- lvBa --- rBa1                (blue)
     *      |       |        `-- rBa2                (grey)
     *      |       `-- rBb                          (orange)
     *      |-- lvC --- lvCa --- rCa1                (orange)
     *      |       |        `-- rCa2                (grey)
     *      |       `-- rCb                          (blue)
     *      |-- lvD --- rDa                          (orange)
     *      |       `-- rDb                          (blue)
     *      |-- rE                                   (orange)
     *      `-- rF                                   (blue)
     * Note that:
     *     - nodes
     *          - are all named lv* (for 'level')
     *          - are all Q*Layouts
     *     - terminal leaves
     *          - are all named r* (I forgot why)
     *          - are all empty QLabels
     *          - are the only colored items
     *     - buttons q? have not been represented here, but are associated
     *       with each lv?
     */

    int buttonsize = 8 ;
    int D = 35 ;
    int U = 35 ;
    int L = 35 ;
    int R = 35 ;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            rAa1[3*i+j]->setStyleSheet("background-color: red;") ;
            lvAa1->addWidget(rAa1[3*i+j], i, j) ;
            rAa1[3*i+j]->setFixedSize(buttonsize, buttonsize) ;
        }
    }
    lvAa->addLayout(lvAa1) ;
    lvAa->addWidget(rAa2) ;
    rAa2->setStyleSheet("background-color: grey;") ;
    rAa2->setFixedSize(L, D) ;
    lvAb->addWidget(rAb1) ;
    rAb1->setStyleSheet("background-color: blue;") ;
    rAb1->setFixedSize(R, U);
    lvAb->addWidget(rAb2) ;
    rAb2->setStyleSheet("background-color: orange;") ;
    rAb2->setFixedSize(R, D) ;
    lvA->addLayout(lvAa) ;
    lvA->addLayout(lvAb) ;

    lvBa->addWidget(rBa1) ;
    rBa1->setStyleSheet("background-color: blue;") ;
    rBa1->setFixedSize(L, U) ;
    lvBa->addWidget(rBa2) ;
    rBa2->setStyleSheet("background-color: grey;") ;
    rBa2->setFixedSize(L, D) ;
    lvB->addLayout(lvBa) ;
    lvB->addWidget(rBb) ;
    rBb->setStyleSheet("background-color: orange;") ;
    rBb->setFixedSize(L, U+D+10) ;

    lvCa->addWidget(rCa1) ;
    rCa1->setStyleSheet("background-color: orange;") ;
    rCa1->setFixedSize(L, U) ;
    lvCa->addWidget(rCa2) ;
    rCa2->setStyleSheet("background-color: grey;") ;
    rCa2->setFixedSize(L, D) ;
    lvC->addLayout(lvCa) ;
    lvC->addWidget(rCb) ;
    rCb->setStyleSheet("background-color: blue;") ;
    rCb->setFixedSize(L, U+D+10) ;

    lvD->addWidget(rDa) ;
    rDa->setStyleSheet("background-color: orange;") ;
    rDa->setFixedSize(L, U+D+10) ;
    lvD->addWidget(rDb) ;
    rDb->setStyleSheet("background-color: blue;") ;
    rDb->setFixedSize(R, U+D+10) ;

    lvE->addWidget(rE) ;
    rE->setStyleSheet("background-color: orange;") ;
    rE->setFixedSize(L+R+10, U+D+10) ;

    lvF->addWidget(rF) ;
    rF->setStyleSheet("background-color: blue;") ;
    rF->setFixedSize(L+R+10, U+D+10) ;


    qA->setLayout(lvA) ;
    qA->setFixedSize(100, 100) ;
    qB->setLayout(lvB) ;
    qB->setFixedSize(100, 100) ;
    qC->setLayout(lvC) ;
    qC->setFixedSize(100, 100) ;
    qD->setLayout(lvD) ;
    qD->setFixedSize(100, 100) ;
    qE->setLayout(lvE) ;
    qE->setFixedSize(100, 100) ;
    qF->setLayout(lvF) ;
    qF->setFixedSize(100, 100) ;

    base->addWidget(qA) ;
    base->addWidget(qB) ;
    base->addWidget(qC) ;
    base->addWidget(qD) ;
    base->addWidget(qE) ;
    base->addWidget(qF) ;
    base->addWidget(capture) ;
    setLayout(base) ;

    connect(qA, SIGNAL(clicked()), m_parent, SLOT(setlayout_full())) ;
    connect(qB, SIGNAL(clicked()), m_parent, SLOT(setlayout_diagramhybrid())) ;
    connect(qC, SIGNAL(clicked()), m_parent, SLOT(setlayout_statehybrid())) ;
    connect(qD, SIGNAL(clicked()), m_parent, SLOT(setlayout_hybrid())) ;
    connect(qE, SIGNAL(clicked()), m_parent, SLOT(setlayout_diagram())) ;
    connect(qF, SIGNAL(clicked()), m_parent, SLOT(setlayout_state())) ;
    connect(capture, SIGNAL(clicked()), m_parent, SLOT(screenshot())) ;
}

void LayoutSelector::closeEvent (QCloseEvent * event) {
    closed() ;
    event->accept() ;
}
