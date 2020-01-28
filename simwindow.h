#pragma once

#include <iostream>
#include <QtWidgets>
#include <QTimer>
#include "constdisplayer.h"
#include "statedisplayer.h"
#include "flowdisplayer.h"
#include "actionbutton.h"
#include "calculator.h"
#include "helpwin.h"
#include "timemgr.h"
#include "const.h"
#include "state.h"
#include "plotwindow.h"

class SimWindow : public QWidget {
    Q_OBJECT
public:
    SimWindow () ;

signals:
     void refresh () ;

public slots:
    void getOutputCst() ;
    void getOutputStt() ;
    void getInputCst() ;
    void getInputStt() ;
    void PAUSE () ;
    void SKIP () ;
    void PLAY () ;
    void PING () ;

private:
    QButtonGroup * m_playgroup ;
    QButtonGroup * m_skipgroup ;
    ActionButton * m_actPlay ;
    QRadioButton * m_play1 ;
    QRadioButton * m_skip1 ;
    QRadioButton * m_play2 ;
    QRadioButton * m_skip2 ;
    QRadioButton * m_play5 ;
    QRadioButton * m_skip5 ;
    QRadioButton * m_play10 ;
    QRadioButton * m_skip10 ;
    QPushButton * m_actSavestate ;
    QPushButton * m_actLoadstate ;
    QPushButton * m_actSaveconst ;
    QPushButton * m_actLoadconst ;
    QPushButton * m_helpButton ;
    QPushButton * m_actSetPlay ;
    QPushButton * m_actSetSkip ;
    QPushButton * m_actPause ;
    QPushButton * m_actSkip ;
    QPushButton * m_circul ;
    QPushButton * m_eBox ;
    QPushButton * m_pBox ;
    QHBoxLayout * m_selectbox ;
    QHBoxLayout * m_simArea ;
    QVBoxLayout * m_playbox ;
    QVBoxLayout * m_skipbox ;
    QGridLayout * m_grid ;
    QWidget * m_select ;
    ConstDisplayer * m_displamb ;
    ConstDisplayer * m_disptauT ;
    ConstDisplayer * m_disptauS ;
    ConstDisplayer * m_dispTe ;
    ConstDisplayer * m_dispSe ;
    ConstDisplayer * m_dispTp ;
    ConstDisplayer * m_dispSp ;
    ConstDisplayer * m_dispdt ;
    ConstDisplayer * m_dispM ;
    Calculator * m_calc ;
    TimeMgr * m_dispTIME ;
    HelpWin * m_help ;
    QTimer * m_timer ;
    Const * m_Cst ;
    Const * m_Aim ;
    State * m_Stt ;
    PlotWindow * m_plot ;
};
