#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include "statedisplayer.h"
#include "flowdisplayer.h"


class SimulView : public QWidget {
    Q_OBJECT
public:
    SimulView (StateDisplayer *, FlowDisplayer *, StateDisplayer *) ;
};
