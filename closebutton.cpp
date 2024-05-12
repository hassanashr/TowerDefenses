#include "closebutton.h"


CloseButton::CloseButton(QWidget* parent): QObject(), QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/img/Resources/X.png").scaled(50, 50));
    setPos(750, 0);
    original = parent;
}


void CloseButton::mousePressEvent(QGraphicsSceneMouseEvent * e){

}
