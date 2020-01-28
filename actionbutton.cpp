#include "actionbutton.h"

ActionButton::ActionButton (QWidget * parent, QString helptext, QStyle::StandardPixmap iconIdx) {
    setFixedSize(85, 90) ;
    m_parent = parent ;
    setParent(m_parent) ;
    setToolTip(helptext) ;

    m_label = new QLabel (this) ;
    QIcon icon = style()->standardIcon(iconIdx);
    QPixmap pixmap = icon.pixmap(QSize(80, 80));
    m_label->setPixmap(pixmap) ;

}
