#include <QApplication>
#include "simwindow.h"
#include "const.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv) ;

    SimWindow simul ;
    simul.show() ;

    auto res = app.exec() ;
    return res ;
}
