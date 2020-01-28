#include "simwindow.h"

SimWindow::SimWindow () {
    setFixedSize(900, 600) ;

    m_Cst = new Const ;
    m_Aim = new Const ;
    m_Stt = new State ;

    // TOOLBAR
    m_actSavestate = new ActionButton (this, "Save State (*.stt)", QStyle::SP_DialogSaveButton) ;
    m_actLoadstate = new ActionButton (this, "Load State (*.stt)", QStyle::SP_DialogOpenButton) ;
    m_actSaveconst = new ActionButton (this, "Save Const (*.cst)", QStyle::SP_DialogSaveButton) ;
    m_actLoadconst = new ActionButton (this, "Load Const (*.cst)", QStyle::SP_DialogOpenButton) ;
    m_actPlay = new ActionButton (this, "Play", QStyle::SP_MediaPlay) ;
    m_actPause = new ActionButton (this, "Pause", QStyle::SP_MediaPause) ;
    m_actSkip = new ActionButton (this, "Skip", QStyle::SP_MediaSkipForward) ;
    m_helpButton = new ActionButton (this, "Help", QStyle::SP_MessageBoxQuestion) ;
    m_dispTe = new ConstDisplayer("Tₑ*", this, m_Cst, m_Aim, Te, "Température à l'équateur (équilibre)") ;
    m_dispSe = new ConstDisplayer("Sₑ*", this, m_Cst, m_Aim, Se, "Salinité à l'équateur (équilibre)") ;
    m_dispTp = new ConstDisplayer("Tₚ*", this, m_Cst, m_Aim, Tp, "Température au pôle (équilibre)") ;
    m_dispSp = new ConstDisplayer("Sₚ*", this, m_Cst, m_Aim, Sp, "Salinité au pôle (équilibre)") ;
    m_dispdt = new ConstDisplayer("dt", this, m_Cst, m_Aim, dt, "Paramètre de discrétisation") ;
    m_displamb = new ConstDisplayer("λ", this, m_Cst, m_Aim, lambda, "Flux") ;
    m_dispM = new ConstDisplayer("M₀", this, m_Cst, m_Aim, M0, "Masse océanique") ;
    m_disptauT = new ConstDisplayer("τₜ", this, m_Cst, m_Aim, tauT, "Temps de relaxation en température") ;
    m_disptauS = new ConstDisplayer("τₛ", this, m_Cst, m_Aim, tauS, "Temps de relaxation en salinité") ;
    m_dispTIME = new TimeMgr(this, m_Cst) ;

    m_calc = new Calculator (this, m_Stt, m_Cst, m_Aim) ;
    m_help = new HelpWin () ;

    connect(m_actSavestate, SIGNAL(clicked()), this, SLOT(getOutputStt())) ;
    connect(m_actLoadstate, SIGNAL(clicked()), this, SLOT(getInputStt())) ;
    connect(m_actSaveconst, SIGNAL(clicked()), this, SLOT(getOutputCst())) ;
    connect(m_actLoadconst, SIGNAL(clicked()), this, SLOT(getInputCst())) ;
    connect(m_helpButton, SIGNAL(clicked()), m_help, SLOT(exec())) ;

    m_playgroup = new QButtonGroup (this) ;
    m_play1 = new QRadioButton("1") ;
    m_play2 = new QRadioButton("2") ;
    m_play5 = new QRadioButton("5") ;
    m_play10 = new QRadioButton("9") ;
    m_play1->setChecked(true);
    m_playbox = new QVBoxLayout ;
    m_playgroup->addButton(m_play1) ;
    m_playgroup->addButton(m_play2) ;
    m_playgroup->addButton(m_play5) ;
    m_playgroup->addButton(m_play10) ;
    m_playbox->addWidget(new QLabel ("Play")) ;
    m_playbox->addWidget(m_play1) ;
    m_playbox->addWidget(m_play2) ;
    m_playbox->addWidget(m_play5) ;
    m_playbox->addWidget(m_play10) ;

    m_skipgroup = new QButtonGroup (this) ;
    m_skip1 = new QRadioButton("1") ;
    m_skip2 = new QRadioButton("2") ;
    m_skip5 = new QRadioButton("5") ;
    m_skip10 = new QRadioButton("9") ;
    m_skip1->setChecked(true);
    m_skipbox = new QVBoxLayout ;
    m_skipgroup->addButton(m_skip1) ;
    m_skipgroup->addButton(m_skip2) ;
    m_skipgroup->addButton(m_skip5) ;
    m_skipgroup->addButton(m_skip10) ;
    m_skipbox->addWidget(new QLabel ("Skip")) ;
    m_skipbox->addWidget(m_skip1) ;
    m_skipbox->addWidget(m_skip2) ;
    m_skipbox->addWidget(m_skip5) ;
    m_skipbox->addWidget(m_skip10);

    m_selectbox = new QHBoxLayout ;
    m_selectbox->addLayout(m_playbox) ;
    m_selectbox->addLayout(m_skipbox) ;
    m_select = new QWidget (this) ;
    m_select->setLayout(m_selectbox) ;

    m_timer = new QTimer (this) ;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(PING())) ;
    connect(m_actSkip, SIGNAL(clicked()), this, SLOT(SKIP())) ;
    connect(m_actPlay, SIGNAL(clicked()), this, SLOT(PLAY())) ;
    connect(m_actPause, SIGNAL(clicked()), this, SLOT(PAUSE())) ;

    m_plot = new PlotWindow (m_Stt, m_timer) ;
    m_plot->show () ;

    m_grid = new QGridLayout ;
    m_grid->addWidget(m_dispTe, 0, 0) ;
    m_grid->addWidget(m_dispSe, 1, 0) ;
    m_grid->addWidget(m_dispdt, 2, 0) ;
    m_grid->addWidget(m_dispTIME, 3, 0) ;
    m_grid->addWidget(m_displamb, 4, 0) ;
    m_grid->addWidget(m_dispM, 5, 0) ;
    m_grid->addWidget(m_actPlay, 0, 1) ;
    m_grid->addWidget(m_actPause, 0, 2) ;
    m_grid->addWidget(m_actSkip, 0, 3) ;
    m_grid->addWidget(m_actSavestate, 0, 4) ;
    m_grid->addWidget(m_actLoadstate, 0, 5) ;
    m_grid->addWidget(m_actSaveconst, 0, 6) ;
    m_grid->addWidget(m_actLoadconst, 0, 7) ;
    m_grid->addWidget(m_helpButton, 0, 8) ;
    m_grid->addWidget(m_dispTp, 0, 9) ;
    m_grid->addWidget(m_dispSp, 1, 9) ;
    m_grid->addWidget(m_disptauT, 2, 9) ;
    m_grid->addWidget(m_disptauS, 3, 9) ;
    m_grid->addWidget(m_select, 4, 9, 2, 1) ;

    m_simArea = new QHBoxLayout ;
    m_eBox = new StateDisplayer ("Equator", this, m_Stt, equator) ;
    m_pBox = new StateDisplayer ("Pole", this, m_Stt, pole) ;
    m_circul = new FlowDisplayer (this, m_Stt) ;
    m_simArea->addWidget(m_eBox) ;
    m_simArea->addWidget(m_circul) ;
    m_simArea->addWidget(m_pBox) ;
    m_grid->addLayout(m_simArea, 1, 1, 5, 8) ;

    setLayout(m_grid) ;
    m_Cst->read(QString ("/home/vanille/ALGO/TIPE/Simul/build-Circulation-Desktop-Debug/default.cst")) ;
}

void SimWindow::getInputCst() {
    QString input = QFileDialog::getOpenFileName(this, "Load Const", QString(), "Const (*.cst)") ;
    m_Cst->read(input) ;
    m_Aim->read(input) ;
    refresh() ;
}

void SimWindow::getInputStt() {
    QString input = QFileDialog::getOpenFileName(this, "Load State", QString(), "State (*.stt)") ;
    m_Stt->read(input) ;
    refresh() ;
}

void SimWindow::getOutputCst() {
    QString output = QFileDialog::getSaveFileName(this, "Save Const", QString(), "Const (*.cst)") ;
    m_Aim->write(output) ;
}

void SimWindow::getOutputStt() {
    QString output = QFileDialog::getSaveFileName(this, "Save State", QString(), "State (*.stt)") ;
    m_Stt->write(output) ;
}

void SimWindow::SKIP () {
    //printf("SKIP!\n") ;
    int nbSkip = 1 ;
    //printf("nbRepeat:%d\n", m_skipgroup->checkedId()) ;
    switch (m_skipgroup->checkedId()) {
        case -2: nbSkip = 1 ; break ;
        case -3: nbSkip = 2 ; break ;
        case -4: nbSkip = 5 ; break ;
        case -5: nbSkip = 10 ; break ;
    }
    for (int i = 0; i < nbSkip; i++) {
        //printf("~ %d\n", i) ;
        m_calc->step() ;
        m_plot->thermohalineDataSlot() ;
        m_dispTIME->tick() ;
        refresh() ;
    }
}

void SimWindow::PLAY () {
    //printf("PLAY!\n") ;
    int freq = 1 ;
    //printf("nbRepeat:%d\n", m_skipgroup->checkedId()) ;
    switch (m_playgroup->checkedId()) {
        case -2: freq = 1 ; break ;
        case -3: freq = 2 ; break ;
        case -4: freq = 5 ; break ;
        case -5: freq = 10 ; break ;
    }
    m_timer->setInterval(1000/freq) ;
    m_timer->start() ;
}

void SimWindow::PAUSE () {
    //printf("PAUSE!\n") ;
    m_timer->stop() ;
}

void SimWindow::PING () {
    m_calc->step() ;
    m_dispTIME->tick() ;
    refresh() ;
}
