#pragma once

#include <iostream>
#include <QVBoxLayout>
#include <QTextStream>
#include <QPushButton>
#include <QTextEdit>
#include <QDialog>
#include <QFile>

class HelpWin : public QDialog {
public:
    HelpWin () ;
private:
    QVBoxLayout * m_mainbox ;
    QPushButton * m_close ;
    QTextEdit * m_help ;
};

