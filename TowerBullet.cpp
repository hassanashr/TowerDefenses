#include "TowerBullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "enemy.h"
#include "Boosters.h"
int TowerBullet::count = 0;
TowerBullet::TowerBullet(QGraphicsScene* Scene, Game* game):Structure() {
    setPixmap(QPixmap(":/img/Bomb3.png"));
    QTimer * move_timer = new QTimer(this);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(50);
    parent = game->gameScene;
    parentGame = game;
    damage = 1;
    damageIncreasedCount = 0;
}

void TowerBullet::move(){
    double theta = rotation();

    double dy = stepsize_spirte * qSin(qDegreesToRadians(theta));
    double dx = stepsize_spirte * qCos(qDegreesToRadians(theta));
    setPos(pos().x() + dx, pos().y() + dy);

    QList<QGraphicsItem *> collidedItems = collidingItems();
    bool collided = false;

    for (auto item : collidedItems) {
        if (typeid(*item) == typeid(Enemy)) {
            Enemy* enemy = dynamic_cast<Enemy*>(item);
            enemy->decreaseHealth(damage);
            qDebug() << "Bullet collided with enemy";

            if (enemy->getHealth() <= 0) {
                scene()->removeItem(enemy);
                delete enemy;
                count++;
                qDebug() << "Enemy destroyed! Count: " << count;
                collided = true;
            }
        } else if (typeid(*item) == typeid(Booster)) {
            Booster* booster = dynamic_cast<Booster*>(item);
            scene()->removeItem(booster);
            delete booster;
            qDebug() << "Booster removed";
            collided = true; // Set collided to true to indicate a collision
        }
    }

    if (collided) {
        scene()->removeItem(this);
        delete this; // Delete the bullet item
        qDebug() << "Bullet removed";
    }

    if (count >= 20 * (damageIncreasedCount + 1)) {
        damage = damage + (damage * 0.1);
        damageIncreasedCount++;
        qDebug() << "Increased bullet damage to" << damage << "after" << count << "kills";
    }
}
