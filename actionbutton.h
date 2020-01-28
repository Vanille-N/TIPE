#pragma once

#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QStyle>
#include <QLabel>

class ActionButton : public QPushButton {
    Q_OBJECT
public:
    ActionButton (QWidget *, QString,  QStyle::StandardPixmap) ;

private:
    QString m_helptext ;
    QWidget * m_parent ;
    QLabel * m_label ;
};

