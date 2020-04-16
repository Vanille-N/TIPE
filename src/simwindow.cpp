#include "simwindow.h"

SimWindow::SimWindow () {
    move(5, 5) ;
    setFixedSize(1215, 680) ;
    m_grid = new QGridLayout () ;
    setLayout(m_grid) ;
    m_playing = false ;

    m_Aim = new Const (false) ;

    for (int K = 0; K < NB_POINTS; K++) {
        m_Cst.push_back(new Const ((bool)K)) ;
        m_Stt.push_back(new State ()) ;
    }

    // TOOLBAR
    m_actSavestate = new ActionButton (this, "Save State (*.stt)", QStyle::SP_DialogSaveButton) ;
    m_actLoadstate = new ActionButton (this, "Load State (*.stt)", QStyle::SP_DialogOpenButton) ;
    m_actSaveconst = new ActionButton (this, "Save Const (*.cst)", QStyle::SP_DialogSaveButton) ;
    m_actLoadconst = new ActionButton (this, "Load Const (*.cst)", QStyle::SP_DialogOpenButton) ;
    m_actPlayPause = new ActionButton (this, "Play", QStyle::SP_MediaPlay) ;
    //m_actPause = new ActionButton (this, "Pause", QStyle::SP_MediaPause) ;
    m_actSkip = new ActionButton (this, "Skip", QStyle::SP_MediaSkipForward) ;
    m_helpButton = new ActionButton (this, "Help", QStyle::SP_MessageBoxQuestion) ;
    m_dispTe = new ConstDisplayer ("Tₑ*", this, m_Cst[0], m_Aim, Te, "Température à l'équateur (équilibre), °C") ;
    m_dispSe = new ConstDisplayer ("Sₑ*", this, m_Cst[0], m_Aim, Se, "Salinité à l'équateur (équilibre), psu") ;
    m_dispTp = new ConstDisplayer ("Tₚ*", this, m_Cst[0], m_Aim, Tp, "Température au pôle (équilibre), °C") ;
    m_dispSp = new ConstDisplayer ("Sₚ*", this, m_Cst[0], m_Aim, Sp, "Salinité au pôle (équilibre), psu") ;
    m_dispdt = new ConstDisplayer ("dt", this, m_Cst[0], m_Aim, dt, "Paramètre de discrétisation, s") ;
    m_displamb = new ConstDisplayer ("λ", this, m_Cst[0], m_Aim, lambda, "Flux, m³⋅s⁻¹") ;
    m_dispM = new ConstDisplayer ("M₀", this, m_Cst[0], m_Aim, M0, "Masse océanique, kg") ;
    m_disptauT = new ConstDisplayer ("τₜ", this, m_Cst[0], m_Aim, tauT, "Temps de relaxation en température, s") ;
    m_disptauS = new ConstDisplayer ("τₛ", this, m_Cst[0], m_Aim, tauS, "Temps de relaxation en salinité, s") ;
    m_dispTIME = new TimeMgr (this, m_Cst[0]) ;

    m_layoutSelect = new LayoutSelector (this) ;
    //m_layoutSelect->show() ;
    m_launchLayoutSelect = new QPushButton ("Layout", this) ;
    m_launchLayoutSelect->setFixedSize(70, 70) ;
    connect(m_launchLayoutSelect, SIGNAL(clicked()), this, SLOT(launchLayoutSelect())) ;

    m_calc = new Calculator (this, m_Stt, m_Cst, m_Aim, &m_cplVal, &m_eqmVal) ;
    m_help = new HelpWin () ;

    m_toggleEquilibrium = new QPushButton ("Équilibre\n(ON)") ;
    m_toggleCoupling = new QPushButton ("Couplage\n(ON)") ;
    m_toggleEquilibrium->setFont(QFont ("ubuntu", 11)) ;
    m_toggleCoupling->setFont(QFont ("ubuntu", 11)) ;
    m_toggleEquilibrium->setFixedSize(70, 70) ;
    m_toggleCoupling->setFixedSize(70, 70) ;
    m_eqmVal = true ;
    m_cplVal = true ;
    connect(m_toggleCoupling, SIGNAL(clicked()), this, SLOT(toggleCpl())) ;
    connect(m_toggleEquilibrium, SIGNAL(clicked()), this, SLOT(toggleEqm())) ;

    connect(m_actSavestate, SIGNAL(clicked()), this, SLOT(getOutputStt())) ;
    connect(m_actLoadstate, SIGNAL(clicked()), this, SLOT(getInputStt())) ;
    connect(m_actSaveconst, SIGNAL(clicked()), this, SLOT(getOutputCst())) ;
    connect(m_actLoadconst, SIGNAL(clicked()), this, SLOT(getInputCst())) ;
    connect(m_helpButton, SIGNAL(clicked()), m_help, SLOT(exec())) ;

    m_playgroup = new QButtonGroup (this) ;
    m_play1 = new QRadioButton("-") ;
    m_play5 = new QRadioButton("") ;
    m_play10 = new QRadioButton("+") ;
    m_play10->setChecked(true);
    m_playbox = new QVBoxLayout ;
    m_playgroup->addButton(m_play1) ;
    m_playgroup->addButton(m_play5) ;
    m_playgroup->addButton(m_play10) ;
    auto label = new QLabel ("Play") ;
    label->setFont(QFont("ubuntu", 15)) ;
    m_playbox->addWidget(label) ;
    m_playbox->addWidget(m_play1) ;
    m_playbox->addWidget(m_play5) ;
    m_playbox->addWidget(m_play10) ;

    m_skipgroup = new QButtonGroup (this) ;
    m_skip1 = new QRadioButton("-") ;
    m_skip5 = new QRadioButton("") ;
    m_skip10 = new QRadioButton("+") ;
    m_skip1->setChecked(true);
    m_skipbox = new QVBoxLayout ;
    m_skipgroup->addButton(m_skip1) ;
    m_skipgroup->addButton(m_skip5) ;
    m_skipgroup->addButton(m_skip10) ;
    auto label2 = new QLabel ("Skip") ;
    label2->setFont(QFont("ubuntu", 15)) ;
    m_skipbox->addWidget(label2) ;
    m_skipbox->addWidget(m_skip1) ;
    m_skipbox->addWidget(m_skip5) ;
    m_skipbox->addWidget(m_skip10);

    m_selectbox = new QHBoxLayout ;
    m_selectbox->addLayout(m_playbox) ;
    m_selectbox->addLayout(m_skipbox) ;
    m_select = new QWidget (this) ;
    m_select->setLayout(m_selectbox) ;
    m_select->setFixedSize(140, 140) ;

    m_timer = new QTimer (this) ;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(PING())) ;
    connect(m_actSkip, SIGNAL(clicked()), this, SLOT(SKIP())) ;
    connect(m_actPlayPause, SIGNAL(clicked()), this, SLOT(PLAYPAUSE())) ;
    //connect(m_actPause, SIGNAL(clicked()), this, SLOT(PAUSE())) ;

    m_diagramplot = new DiagramPlot (m_Stt, m_timer, this) ;
    m_diagramplot->show () ;
    m_stateplot = new StatePlot (m_Stt, m_Cst, this) ;
    m_stateplot->show () ;
    connect(m_timer, SIGNAL(timeout()), m_stateplot, SLOT(dataSlot())) ;

    m_eBox = new StateDisplayer ("Équateur", this, m_Stt, equator) ;
    m_pBox = new StateDisplayer ("Pôle", this, m_Stt, pole) ;
    m_circul = new FlowDisplayer (this, m_Stt[0]) ;
    m_simArea = new SimulView (m_eBox, m_circul, m_pBox) ;

    setlayout_full() ;
    connect(m_layoutSelect, SIGNAL(closed()), this, SLOT(setlayout_full())) ;
    connect(this, SIGNAL(closed()), m_layoutSelect, SLOT(close())) ;
}

void SimWindow::getInputCst() {
    QString input = QFileDialog::getOpenFileName(this, "Load Const", QString(), "Const (*.cst)") ;
    m_Aim->read(input) ;
    for (int K = 0; K < NB_POINTS; K++) {
        m_Cst[K]->read(input) ;
    }
    refresh() ;
}

void SimWindow::getInputStt() {
    QString input = QFileDialog::getOpenFileName(this, "Load State", QString(), "State (*.stt)") ;
    for (int K = 0; K < NB_POINTS; K++) {
        m_Stt[K]->read(input) ;
    }
    refresh() ;
}

void SimWindow::getOutputCst() {
    QString output = QFileDialog::getSaveFileName(this, "Save Const", QString(), "Const (*.cst)") ;
    m_Aim->write(output) ;
}

void SimWindow::getOutputStt() {
    QString output = QFileDialog::getSaveFileName(this, "Save State", QString(), "State (*.stt)") ;
    m_Stt[0]->write(output) ;
}

void SimWindow::SKIP () {
    if (m_playing) return ;
    int nbSkip = 1 ;
    switch (m_skipgroup->checkedId()) {
        case -2: nbSkip = 1 ; break ;
        case -3: nbSkip = 5 ; break ;
        case -4: nbSkip = 10 ; break ;
    }
    for (int i = 0; i < nbSkip; i++) {
        m_calc->step() ;
        m_diagramplot->dataSlot() ;
        m_stateplot->dataSlot() ;
        m_dispTIME->tick() ;
        refresh() ;
    }
}

void SimWindow::PLAYPAUSE () {
    if (m_playing) {
        m_timer->stop() ;
        m_playing = false ;
        m_actPlayPause->setImage(QStyle::SP_MediaPlay) ;
        m_actPlayPause->setToolTip("Play") ;
    } else {
        int freq = 1 ;
        switch (m_playgroup->checkedId()) {
            case -2: freq = 1 ; break ;
            case -3: freq = 5 ; break ;
            case -4: freq = 10 ; break ;
        }
        m_timer->setInterval(1000/freq) ;
        m_timer->start() ;
        m_playing = true ;
        m_actPlayPause->setImage(QStyle::SP_MediaPause) ;
        m_actPlayPause->setToolTip("Pause") ;
    }
}

//void SimWindow::PAUSE () {
//    m_timer->stop() ;
//}

void SimWindow::PING () {
    m_calc->step() ;
    m_dispTIME->tick() ;
    refresh() ;
}

void SimWindow::toggleCpl () {
    if (m_cplVal) {
        m_cplVal = false ;
        m_toggleCoupling->setText("Couplage\n(OFF)") ;
    } else {
        m_cplVal = true ;
        m_toggleCoupling->setText("Couplage\n(ON)") ;
    }
}

void SimWindow::toggleEqm () {
    if (m_eqmVal) {
        m_eqmVal = false ;
        m_toggleEquilibrium->setText("Équilibre\n(OFF)") ;
    } else {
        m_eqmVal = true ;
        m_toggleEquilibrium->setText("Équilibre\n(ON)") ;
    }
}


void SimWindow::setlayout_full () {
    while (m_grid->takeAt(0) != 0) ;
    m_grid->addWidget(m_dispSe, 0, 0) ; m_dispSe->show() ;
    m_grid->addWidget(m_dispSp, 0, 1) ; m_dispSp->show() ;
    m_grid->addWidget(m_disptauS, 0, 2) ; m_disptauS->show() ;
    m_grid->addWidget(m_displamb, 0, 3) ; m_displamb->show() ;
    m_grid->addWidget(m_dispTe, 1, 0) ; m_dispTe->show() ;
    m_grid->addWidget(m_dispTp, 1, 1) ; m_dispTp->show() ;
    m_grid->addWidget(m_disptauT, 1, 2) ; m_disptauT->show() ;
    m_grid->addWidget(m_dispM, 1, 3) ; m_dispM->show() ;
    m_grid->addWidget(m_select, 0, 4, 2, 2) ; m_select->show() ;
    m_grid->addWidget(m_toggleCoupling, 3, 4) ; m_toggleCoupling->show() ;
    m_grid->addWidget(m_toggleEquilibrium, 3, 5) ; m_toggleEquilibrium->show() ;
    m_grid->addWidget(m_dispTIME, 2, 0) ; m_dispTIME->show() ;
    m_grid->addWidget(m_dispdt, 2, 1) ; m_dispdt->show() ;
    m_grid->addWidget(m_actPlayPause, 2, 2) ; m_actPlayPause->show() ;
    m_grid->addWidget(m_actSkip, 2, 3) ; m_actSkip->show() ;
    m_grid->addWidget(m_helpButton, 2, 4) ; m_helpButton->show() ;
    m_grid->addWidget(m_launchLayoutSelect, 2, 5) ; m_launchLayoutSelect->show() ;
    m_grid->addWidget(m_actLoadconst, 3, 0) ; m_actLoadconst->show() ;
    m_grid->addWidget(m_actSaveconst, 3, 1) ; m_actSaveconst->show() ;
    m_grid->addWidget(m_actLoadstate, 3, 2) ; m_actLoadstate->show() ;
    m_grid->addWidget(m_actSavestate, 3, 3) ; m_actSavestate->show() ;
    m_grid->addWidget(m_simArea, 4, 0, 5, 6) ; m_simArea->show() ;
    m_grid->addWidget(m_stateplot, 0, 6, 4, 6) ; m_stateplot->show() ;
    m_stateplot->setFixedSize(700, 300) ;
    m_grid->addWidget(m_diagramplot, 4, 6, 6, 6) ; m_diagramplot->show() ;
    m_diagramplot->setFixedSize(700, 350) ;
}

void SimWindow::setlayout_statehybrid () {
    while (m_grid->takeAt(0) != 0) ;
    m_dispSe->hide() ;
    m_dispSp->hide() ;
    m_disptauS->hide() ;
    m_displamb->hide() ;
    m_dispTe->hide() ;
    m_dispTp->hide() ;
    m_disptauT->hide() ;
    m_dispM->hide() ;
    m_select->hide() ;
    m_toggleCoupling->hide() ;
    m_toggleEquilibrium->hide() ;
    m_dispTIME->hide() ;
    m_dispdt->hide() ;
    m_actPlayPause->hide() ;
    m_launchLayoutSelect->hide() ;
    m_actSkip->hide() ;
    m_helpButton->hide() ;
    m_actLoadconst->hide() ;
    m_actSaveconst->hide() ;
    m_actLoadstate->hide() ;
    m_actSavestate->hide() ;
    m_grid->addWidget(m_simArea, 1, 0) ; m_simArea->show() ;
    m_grid->addWidget(m_stateplot, 0, 1, 2, 1) ; m_stateplot->show() ;
    m_stateplot->setFixedSize(700, 660) ;
    m_grid->addWidget(m_diagramplot, 0, 0) ; m_diagramplot->show() ;
    m_diagramplot->setFixedSize(480, 300) ;
}

void SimWindow::setlayout_diagramhybrid () {
    while (m_grid->takeAt(0) != 0) ;
    m_dispSe->hide() ;
    m_dispSp->hide() ;
    m_disptauS->hide() ;
    m_displamb->hide() ;
    m_dispTe->hide() ;
    m_dispTp->hide() ;
    m_disptauT->hide() ;
    m_dispM->hide() ;
    m_select->hide() ;
    m_toggleCoupling->hide() ;
    m_toggleEquilibrium->hide() ;
    m_dispTIME->hide() ;
    m_dispdt->hide() ;
    m_actPlayPause->hide() ;
    m_launchLayoutSelect->hide() ;
    m_actSkip->hide() ;
    m_helpButton->hide() ;
    m_actLoadconst->hide() ;
    m_actSaveconst->hide() ;
    m_actLoadstate->hide() ;
    m_actSavestate->hide() ;
    m_grid->addWidget(m_simArea, 1, 0) ; m_simArea->show() ;
    m_grid->addWidget(m_stateplot, 0, 0) ; m_stateplot->show() ;
    m_stateplot->setFixedSize(480, 300) ;
    m_grid->addWidget(m_diagramplot, 0, 1, 2, 1) ; m_diagramplot->show() ;
    m_diagramplot->setFixedSize(700, 660) ;
}

void SimWindow::setlayout_hybrid () {
    while (m_grid->takeAt(0) != 0) ;
    m_dispSe->hide() ;
    m_dispSp->hide() ;
    m_disptauS->hide() ;
    m_displamb->hide() ;
    m_dispTe->hide() ;
    m_dispTp->hide() ;
    m_disptauT->hide() ;
    m_dispM->hide() ;
    m_select->hide() ;
    m_toggleCoupling->hide() ;
    m_toggleEquilibrium->hide() ;
    m_dispTIME->hide() ;
    m_dispdt->hide() ;
    m_actPlayPause->hide() ;
    m_launchLayoutSelect->hide() ;
    m_actSkip->hide() ;
    m_helpButton->hide() ;
    m_actLoadconst->hide() ;
    m_actSaveconst->hide() ;
    m_actLoadstate->hide() ;
    m_actSavestate->hide() ;
    m_simArea->hide() ;
    m_grid->addWidget(m_stateplot, 0, 0) ; m_stateplot->show() ;
    m_stateplot->setFixedSize(580, 660) ;
    m_grid->addWidget(m_diagramplot, 0, 1) ; m_diagramplot->show() ;
    m_diagramplot->setFixedSize(580, 660) ;
}

void SimWindow::setlayout_diagram () {
    while (m_grid->takeAt(0) != 0) ;
    m_dispSe->hide() ;
    m_dispSp->hide() ;
    m_disptauS->hide() ;
    m_displamb->hide() ;
    m_dispTe->hide() ;
    m_dispTp->hide() ;
    m_disptauT->hide() ;
    m_dispM->hide() ;
    m_select->hide() ;
    m_toggleCoupling->hide() ;
    m_toggleEquilibrium->hide() ;
    m_dispTIME->hide() ;
    m_dispdt->hide() ;
    m_actPlayPause->hide() ;
    m_launchLayoutSelect->hide() ;
    m_actSkip->hide() ;
    m_helpButton->hide() ;
    m_actLoadconst->hide() ;
    m_actSaveconst->hide() ;
    m_actLoadstate->hide() ;
    m_actSavestate->hide() ;
    m_simArea->hide() ;
    m_stateplot->hide() ;
    m_grid->addWidget(m_diagramplot, 0, 0) ; m_diagramplot->show() ;
    m_diagramplot->setFixedSize(1190, 660) ;
}

void SimWindow::setlayout_state () {
    while (m_grid->takeAt(0) != 0) ;
    m_dispSe->hide() ;
    m_dispSp->hide() ;
    m_disptauS->hide() ;
    m_displamb->hide() ;
    m_dispTe->hide() ;
    m_dispTp->hide() ;
    m_disptauT->hide() ;
    m_dispM->hide() ;
    m_select->hide() ;
    m_toggleCoupling->hide() ;
    m_toggleEquilibrium->hide() ;
    m_dispTIME->hide() ;
    m_dispdt->hide() ;
    m_actPlayPause->hide() ;
    m_launchLayoutSelect->hide() ;
    m_actSkip->hide() ;
    m_helpButton->hide() ;
    m_actLoadconst->hide() ;
    m_actSaveconst->hide() ;
    m_actLoadstate->hide() ;
    m_actSavestate->hide() ;
    m_simArea->hide() ;
    m_grid->addWidget(m_stateplot, 0, 0) ; m_stateplot->show() ;
    m_stateplot->setFixedSize(1190, 660) ;
    m_diagramplot->hide() ;
}

void SimWindow::launchLayoutSelect () {
    //std::cout << "launch" << std::endl ;
    m_layoutSelect->close() ;
    m_layoutSelect->show() ;
}

void SimWindow::screenshot () {
    QRect rectangle (0, 0, width(), height()) ;
    QPixmap pixmap (rectangle.size()) ;
    render(&pixmap, QPoint(), QRegion(rectangle)) ;
    QString output = QFileDialog::getSaveFileName(this, "Save screenshot", QString(), "PNG (*.png)") ;
    pixmap.save(output, "PNG") ;
}

void SimWindow::closeEvent (QCloseEvent * event) {
    closed() ;
    event->accept() ;
}

