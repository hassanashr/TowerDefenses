#ifndef TOWERBULLET_H
#define TOWERBULLET_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "structure.h"
#include "game.h"
class TowerBullet : public Structure{
    Q_OBJECT
public:
    TowerBullet(QGraphicsScene* Scene, Game* game);
    Game* parentGame;
    QGraphicsScene* parentScene;
      static int count;
    int stepsize_spirte = 10;
      int damage;
    int damageIncreasedCount;
public slots:
    void move();
private:
    int counter;


};



#endif // TOWERBULLET_H
