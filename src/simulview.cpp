#include "simulview.h"

SimulView::SimulView (StateDisplayer * e, FlowDisplayer * f, StateDisplayer * p) {
    auto box = new QHBoxLayout (this) ;
    box->addWidget(e) ;
    box->addWidget(f) ;
    box->addWidget(p) ;
    setLayout(box) ;
    setFixedSize(480, 360) ;
}
