#include <QApplication>
#include "simwindow.h"
#include "const.h"
#include "helpsetup.h"

int main(int argc, char *argv[]) {
    buildHelp() ;
    QApplication app(argc, argv) ;

    SimWindow simul ;
    simul.show() ;

    auto res = app.exec() ;
    return res ;
}
