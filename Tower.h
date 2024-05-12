#ifndef TOWER_H
#define TOWER_H
#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include <QPointF>
#include <QObject>
#include <QGraphicsScene>
#include "structure.h"
#include "healthbar.h"
#include "game.h"


class Tower : public Structure{
    Q_OBJECT
public:
    Tower(QGraphicsScene*, Game*);
    double distanceTo(QGraphicsItem * item);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void fire(const QPointF &attackDest);

    HealthBar* healthBar;
    void changeHealth(int);

    Game* parentGame;
    QGraphicsScene* parentScene;
private:
    QGraphicsPolygonItem * attack_area;
    QPointF attack_dest;
    bool has_target;

};


#endif // TOWER_H
