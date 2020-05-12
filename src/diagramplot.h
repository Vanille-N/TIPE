#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include "qcustomplot.h"
#include "state.h"
#include "circular.h"
#include "metavars.h"

class DiagramPlot : public QWidget {
    Q_OBJECT

public:
    DiagramPlot (QVector<State *> &, QTimer *, QWidget *) ;
    ~DiagramPlot () ;

    void setup () ;
    void setFixedSize (int, int) ;

public slots:
    void dataSlot () ;

private:
    QVector<State *> m_Stt ;
    QVector<Circular *> Xhist ;
    QVector<Circular *> Yhist ;
    QCustomPlot * cp ;
};
