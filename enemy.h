#ifndef ENEMY_H
#define ENEMY_H

#include <castle.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QList>
#include <QObject>
#include <QTimer>
#include <Wall.h>
class Tower;
class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    double levelSpeed[5];
    double levelHealth[5];
    double levelDamage[5];
    double maxHealth;
    double currHealth;
    double currSpeed;
    double currDamage;
    QList<QPixmap> animatedAttack;
    QList<QPixmap> animatedWalk;
    QList<QPixmap> animatedDeath;
    QTimer *animatedWalkTimer;
    QTimer *animatedAttackTimer;
    QTimer *animatedDeathTimer;
    QTimer *movementTimer;
    QTimer *cooldownTimer;
    int currentWalkFrame = 0;
    int currentAttackFrame = 0;
    int currentDeathFrame = 0;
    int animationInterval = 100;
    bool isAttackOver;
    bool toRight;
    bool isDead = false;


public:
    Enemy(int, int);
    ~Enemy();

    //setters
    void setDamage(double d);
    void setSpeed(double s);
    void setHealth(double h);
    void increaseHealth(double h);
    void decreaseHealth(double h);
    void setFrame(int frameIndex);
    //getters
    double getDamage();
    double getSpeed();
    double getHealth();
    double getMaxHealth();

    //functionalities
    void attackCastle(Castle *);
    void attackWall(Wall *);
    void attackTower(Tower *);
    void startWalkingAnimation();
    void startAttackingAnimation();
    void startDeathAnimation();
    void updatePixmap();

public slots:
    void movePath();
    void advanceWalkFrame();
    void advanceAttackFrame();
    void advanceDeathFrame();
    void cooldownTime();
    void die();
};

#endif // ENEMY_H
