#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include "qcustomplot.h"
#include "state.h"
#include "const.h"
#include "circular.h"
#include "timemgr.h"
#include "calculator.h"
#include "metavars.h"

class StatePlot : public QWidget {
    Q_OBJECT

public:
    StatePlot (QVector<State *> &, QVector<Const *> &, QWidget *) ;
    ~StatePlot () ;

    void setup () ;
    void setFixedSize (int, int) ;

public slots:
    void dataSlot () ;

private:
    QVector<State *> m_Stt ;
    QVector<Const *> m_Cst ;
    QVector<Circular *> Te_hist ;
    QVector<Circular *> Tp_hist ;
    QVector<Circular *> Se_hist ;
    QVector<Circular *> Sp_hist ;
    QVector<Circular *> eqTe_hist ;
    QVector<Circular *> eqTp_hist ;
    QVector<Circular *> eqSe_hist ;
    QVector<Circular *> eqSp_hist ;
    QVector<Circular *> Time_hist ;
    QCustomPlot * cp ;
    QCPColorMap * m_colorMap ;
    QCPColorScale * m_colorScale ;
    QCPMarginGroup * m_marginGroup ;
};
