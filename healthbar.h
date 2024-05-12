#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include <QGraphicsRectItem>
#include "structure.h"

class HealthBar
{
public:
    HealthBar(Structure *, int, int, int, int, int);
    ~HealthBar();
    Structure* parent;
    int xPosition, yPosition;
    int width;
    int height;
    void updateBar();
    int borderStroke;
    QGraphicsRectItem * blackBar;
    QGraphicsRectItem * whiteBar;
    QGraphicsRectItem * redBar;

};

#endif // HEALTHBAR_H
