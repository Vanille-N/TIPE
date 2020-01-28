#include "helpwin.h"

HelpWin::HelpWin () {
    QString helpMessage ("") ;
    QString filename ("help.txt") ;
    QFile file (filename) ;
    if (!file.exists()) {
        std::cout << "No such file : " << filename.toStdString() << std::endl ;
        helpMessage = "File not found.\nSorry..." ;
    } else {
        QString line ;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream (&file) ;
            while (!stream.atEnd()){
                line = stream.readLine() ;
                helpMessage = helpMessage + line + "\n" ;
            }
        }
        file.close() ;
    }
    m_help = new QTextEdit() ;
    m_help->setPlainText(helpMessage) ;
    m_help->setReadOnly(true) ;
    m_help->setFont(QFont("Courier")) ;
    m_help->setLineWrapMode(QTextEdit::WidgetWidth) ;

    m_close = new QPushButton("Close") ;

    m_mainbox = new QVBoxLayout ;
    m_mainbox->addWidget(m_help) ;
    m_mainbox->addWidget(m_close) ;

    resize(500, 450) ;
    setLayout(m_mainbox) ;

    connect(m_close, SIGNAL(clicked()), this, SLOT(accept()));
}
