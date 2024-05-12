#include "Tower.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QObject>
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <Wall.h>
#include "enemy.h"
#include <worker.h>
#include <QPointF>
#include <QLineF>
#include <QTransform>
#include<QList>
class TowerBullet;
extern Game *game;
Enemy::Enemy(int x, int y)
{
    setPixmap(QPixmap(":/gameAssets/enemyAssets/Enemy/baseSprite.png")
                  .scaled(32, 32)); //needs some refining until graphically appealing
    setPos(x, y);
    int l = game->getLevel();
    maxHealth = currHealth = levelHealth[l];
    currSpeed = levelSpeed[l];
    currDamage = levelDamage[l];
    for (int i = 1; i <= 11; ++i) {
        QString filePath = ":/enemyAssets/Enemy/run_" + QString::number(i) + ".png";
        animatedWalk.append(QPixmap(filePath));
    }
    for (int i = 1; i <= 12; ++i) {
        QString filePath = ":/enemyAssets/Enemy/attack_" + QString::number(i) + ".png";
        animatedAttack.append(QPixmap(filePath));
    }
    for (int i = 1; i <= 16; ++i) {
        QString filePath = ":/enemyAssets/Enemy/die_" + QString::number(i) + ".png";
        animatedDeath.append(QPixmap(filePath));
    }
    qDebug("Test");
    animatedWalkTimer = new QTimer(this);
    animatedAttackTimer = new QTimer(this);
    animatedDeathTimer = new QTimer(this);
    movementTimer = new QTimer(this);
    cooldownTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Enemy::movePath);
    connect(animatedWalkTimer, &QTimer::timeout, this, &Enemy::advanceWalkFrame);
    connect(animatedAttackTimer, &QTimer::timeout, this, &Enemy::advanceAttackFrame);
    connect(animatedDeathTimer, &QTimer::timeout, this, &Enemy::advanceDeathFrame);
    movementTimer->start(animationInterval);
    isAttackOver = true;
}

Enemy::~Enemy() {}

void Enemy::setDamage(double d)
{
    currDamage = d;
}

void Enemy::setSpeed(double s)
{
    currSpeed = s;
}

void Enemy::setHealth(double h)
{
    currHealth = h;
}

void Enemy::increaseHealth(double h)
{
    currHealth += h;
}

void Enemy::decreaseHealth(double h)
{
    currHealth -= h;
}

double Enemy::getDamage()
{
    return currDamage;
}

double Enemy::getSpeed()
{
    return currSpeed;
}

double Enemy::getHealth()
{
    return currHealth;
}

double Enemy::getMaxHealth()
{
    return maxHealth;
}

void Enemy::attackCastle(Castle* castle) {
    castle->changeHealth(-currDamage);
}

void Enemy::attackWall(Wall *w) {
    w->changeHealth(-currDamage);
}

void Enemy::attackTower(Tower * t)
{
    t->changeHealth(-currDamage);
}

void Enemy::movePath()
{

    if(isDead){
        return;
    }

    //Basic Movement for testing
    int stepsize = 10;
    QLineF ln(pos().x(), pos().y(), 7*61+1, 7*57 + 51);
    double theta = -ln.angle();

    double dy = stepsize * qSin(qDegreesToRadians(theta));
    double dx = stepsize * qCos(qDegreesToRadians(theta));

    //Check direction of movement, right or left
    if(dx < 0)
        toRight = false;
    else
        toRight = true;

    if(!(animatedAttackTimer->isActive()) && !(animatedDeathTimer->isActive())){
        startWalkingAnimation();
    }
    if(animatedWalkTimer->isActive()){
        setPos(pos().x()+dx, pos().y()+dy);
    }
    //stuff for A*

    QList<QGraphicsItem *> collided_items = collidingItems();
    for (auto item : collided_items) {
        if (typeid(*item) == typeid(Wall)) {
            Wall *w = dynamic_cast<Wall *>(item);
            if (isAttackOver){
                attackWall(w);
                isAttackOver = false;
                QTimer::singleShot(1000, this, SLOT(cooldownTime()));
            }
            startAttackingAnimation();
        } else if (typeid(*item) == typeid(Worker)) {
            Worker *w = dynamic_cast<Worker *>(item);
            w->Die();
            startAttackingAnimation();
        } else if (typeid(*item) == typeid(Castle)) {
            Castle* castle = dynamic_cast<Castle*>(item);
            if (isAttackOver){
                attackCastle(castle);
                isAttackOver = false;
                QTimer::singleShot(1000, this, SLOT(cooldownTime()));
            }
            startAttackingAnimation();
        } else if (typeid(*item) == typeid(Tower)) {
            Tower* tower = dynamic_cast<Tower*>(item);
            if (isAttackOver){
                attackTower(tower);
                isAttackOver = false;
                QTimer::singleShot(1200, this, SLOT(cooldownTime()));
            }
            startAttackingAnimation();
        }

}
             if (collided_items.size() == 1) {
        startWalkingAnimation();
    }
             }

void Enemy::startWalkingAnimation()
{
    animatedWalkTimer->start(animationInterval);
    animatedAttackTimer->stop();
    animatedDeathTimer->stop();
}

void Enemy::startAttackingAnimation()
{
    animatedWalkTimer->stop();
    animatedAttackTimer->start(animationInterval);
    animatedDeathTimer->stop();
}

void Enemy::startDeathAnimation()
{
    animatedWalkTimer->stop();
    animatedAttackTimer->stop();
    animatedDeathTimer->start(animationInterval);
}

void Enemy::advanceWalkFrame()
{
    currentWalkFrame = (currentWalkFrame + 1) % animatedWalk.size();
    updatePixmap();
}

void Enemy::advanceAttackFrame()
{
    currentAttackFrame = (currentAttackFrame + 1) % animatedAttack.size();
    updatePixmap();
}

void Enemy::advanceDeathFrame()
{
    currentDeathFrame = (currentDeathFrame + 1) % animatedDeath.size();
    updatePixmap();
}

void Enemy::cooldownTime()
{
    isAttackOver = true;
}

void Enemy::die()
{
    game->gameScene->removeItem(this);
    delete this;
}

void Enemy::updatePixmap()
{
    //This transformation reflects the enemy horizontally
    QTransform transform;
    transform.scale(-1, 1);
    if(toRight){
        if (animatedWalkTimer->isActive()) {
            setPixmap(animatedWalk[currentWalkFrame].scaled(50, 50));
        } else if (animatedAttackTimer->isActive()) {
            setPixmap(animatedAttack[currentAttackFrame].scaled(50, 50));
        } else if (animatedDeathTimer->isActive()) {
            setPixmap(animatedDeath[currentDeathFrame].scaled(50, 50));
        }
    }else{
        if (animatedWalkTimer->isActive()) {
            setPixmap(animatedWalk[currentWalkFrame].scaled(50, 50).transformed(transform));
        } else if (animatedAttackTimer->isActive()) {
            setPixmap(animatedAttack[currentAttackFrame].scaled(50, 50).transformed(transform));
        } else if (animatedDeathTimer->isActive()) {
            setPixmap(animatedDeath[currentDeathFrame].scaled(50, 50).transformed(transform));
        }
    }


}
