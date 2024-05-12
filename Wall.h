#ifndef WALL_H
#define WALL_H
#include "structure.h"
#include <QGraphicsScene>
#include "healthbar.h"
#include <QGraphicsSceneMouseEvent>

class Wall : public Structure
{
public:
    Wall(QGraphicsScene *);
    ~Wall();
    HealthBar* healthBar;
    void changeHealth(int);
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
};

#endif // WALL_H
