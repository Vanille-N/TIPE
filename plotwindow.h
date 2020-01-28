#pragma once

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"
#include "state.h"

namespace Ui {
    class PlotWindow ;
}

class PlotWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit PlotWindow (State *, QTimer *) ;
  ~PlotWindow() ;

  void setupDemo () ;
  void setupThermoHaline (QCustomPlot *) ;

public slots:
  void thermohalineDataSlot () ;

private:
  Ui::PlotWindow * ui ;
  QCPItemTracer * itemDemoPhaseTracer ;
  State * m_Stt ;
};
