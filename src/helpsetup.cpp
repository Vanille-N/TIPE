#include "helpsetup.h"

/* This file is responsible for setting up the environment: default values
 * and help file.
 */

static double cst [NB_CST] = {2000, 295, 50, 38, 32, 30, 2, 10, 8.6} ;

static double stt [NB_STT] = {38, 30, 32, 2} ;

void buildHelp () {
    QString filename_help ("_help_.txt") ;
    QFile file_help (filename_help) ;
    if (!file_help.open(QIODevice::WriteOnly)) return ;
    QTextStream helpS (&file_help);
    helpS << helpMessage ;

    QString filename_cst ("_default_.cst") ;
    QFile file_cst (filename_cst) ;
    if (!file_cst.open(QIODevice::WriteOnly)) return ;
    QDataStream cstS (&file_cst);
    for (int i = 0; i < NB_CST; i++) {
        cstS << cst[i] ;
    }

    QString filename_stt ("_default_.stt") ;
    QFile file_stt (filename_stt) ;
    if (!file_stt.open(QIODevice::WriteOnly)) return ;
    QDataStream sttS (&file_stt);
    for (int i = 0; i < NB_STT; i++) {
        sttS << stt[i] ;
    }
}
