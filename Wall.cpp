#include "Wall.h"
#include <QDebug>
#include <iostream>
Wall::Wall(QGraphicsScene *scene)
    : Structure()
{
    setPixmap(QPixmap(":/mapAssets/Resources/Wall.png").scaled(64, 64));
    parent = scene;
    setType(2);
    setMaxHealth(20);
    setHealth(getMaxHealth());
    setCost((getHealth() / getMaxHealth()) * 100);
    healthBar = nullptr;
}

Wall::~Wall() {}

void Wall::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        changeHealth(-2);

    }else if(e->button() == Qt::RightButton){
        changeHealth(1);

    }
}

void Wall::changeHealth(int healthChange)
{
    if(healthBar == nullptr){
        healthBar = new HealthBar(this, 50, 10, getX() * 61 + 5, getY() * 57 + 55, 1);
    }

    if (getHealth() + healthChange >= getMaxHealth()) {
        setHealth(getMaxHealth());
        delete healthBar;
        healthBar = nullptr;
    } else if (getHealth() + healthChange <= 0) {
        //Destruc object and emit game over
        delete healthBar;
        parent->removeItem(this);
        setType(0);
    } else {
        setHealth(getHealth() + healthChange);
        healthBar->updateBar();
    }
}
