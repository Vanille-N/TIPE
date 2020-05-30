#include "simulview.h"

/* Central area with three buttons side-by-side.
 * Basically does nothing
 */
SimulView::SimulView (StateDisplayer * e, FlowDisplayer * f, StateDisplayer * p) {
    auto box = new QHBoxLayout (this) ;
    box->addWidget(e) ;
    box->addWidget(f) ;
    box->addWidget(p) ;
    setLayout(box) ;
    setFixedSize(480, 360) ;
}
