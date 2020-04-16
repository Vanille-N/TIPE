#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QCloseEvent>

class LayoutSelector : public QWidget {
    Q_OBJECT
public:
    LayoutSelector (QWidget *) ;
    void closeEvent (QCloseEvent *) ;

signals:
    void closed () ;
private:
    QWidget * m_parent ;
};
