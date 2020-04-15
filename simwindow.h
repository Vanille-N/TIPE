#pragma once

#include <iostream>
#include <QtWidgets>
#include <QTimer>
#include <QPixmap>
#include <QRect>
#include <QRegion>
#include <QVector>
#include "constdisplayer.h"
#include "statedisplayer.h"
#include "flowdisplayer.h"
#include "actionbutton.h"
#include "calculator.h"
#include "helpwin.h"
#include "timemgr.h"
#include "const.h"
#include "state.h"
#include "diagramplot.h"
#include "stateplot.h"
#include "layoutselector.h"
#include "simulview.h"

class SimWindow : public QWidget {
    Q_OBJECT
public:
    SimWindow () ;
    bool m_eqmVal ;
    bool m_cplVal ;

signals:
     void refresh () ;
     void closed () ;

public slots:
    void getOutputCst() ;
    void getOutputStt() ;
    void getInputCst() ;
    void getInputStt() ;
    void toggleCpl () ;
    void toggleEqm () ;
    void launchLayoutSelect () ;
    void setlayout_full () ;
    void setlayout_diagramhybrid () ;
    void setlayout_statehybrid () ;
    void setlayout_hybrid () ;
    void setlayout_diagram () ;
    void setlayout_state () ;

    //void PAUSE () ;
    void SKIP () ;
    void PLAYPAUSE () ;
    void PING () ;
    void screenshot () ;

private:
    void closeEvent (QCloseEvent *) ;

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
    ActionButton * m_actSavestate ;
    ActionButton * m_actLoadstate ;
    ActionButton * m_actSaveconst ;
    ActionButton * m_actLoadconst ;
    ActionButton * m_helpButton ;
    ActionButton * m_actPlayPause ;
    ActionButton * m_actSkip ;
    //ActionButton * m_actPause ;
    //ActionButton * m_actSkip ;
    FlowDisplayer * m_circul ;
    StateDisplayer * m_eBox ;
    StateDisplayer * m_pBox ;
    QPushButton * m_toggleCoupling ;
    QPushButton * m_toggleEquilibrium ;
    QPushButton * m_launchLayoutSelect ;
    QHBoxLayout * m_selectbox ;
    QVBoxLayout * m_playbox ;
    QVBoxLayout * m_skipbox ;
    QGridLayout * m_vselect ;
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
    QVector<Const *> m_Cst ;
    Const * m_Aim ;
    QVector<State *> m_Stt ;
    DiagramPlot * m_diagramplot ;
    StatePlot * m_stateplot ;
    LayoutSelector * m_layoutSelect ;
    SimulView * m_simArea ;
    bool m_playing ;
};
