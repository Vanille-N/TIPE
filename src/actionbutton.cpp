#include "actionbutton.h"

ActionButton::ActionButton (QWidget * parent, QString helptext, QStyle::StandardPixmap iconIdx) {
    setFixedSize(70, 70) ;
    setParent(parent) ;
    setToolTip(helptext) ;

    m_label = new QLabel (this) ;
    QIcon icon = style()->standardIcon(iconIdx);
    QPixmap pixmap = icon.pixmap(QSize(70, 70));
    m_label->setPixmap(pixmap) ;

}

void ActionButton::setImage (QStyle::StandardPixmap iconIdx) {
    QIcon icon = style()->standardIcon(iconIdx);
    QPixmap pixmap = icon.pixmap(QSize(70, 70));
    m_label->setPixmap(pixmap) ;
}
