#include "castle.h"
#include <QDebug>
#include "game.h"

Castle::Castle(QGraphicsScene* Scene, Game* game): Structure() {
    parent = game->gameScene;
    parentGame = game;
    setPixmap(QPixmap(":/mapAssets/Resources/Castle.png").scaled(64, 64));
    setMaxHealth(20);
    setType(1);
    setHealth(getMaxHealth());
    healthBar = new HealthBar(this, 400, 50, 0, 0, 3);
    setCost(0);
}

void Castle::mousePressEvent(QGraphicsSceneMouseEvent * e)
{
    if(e->button() == Qt::LeftButton){
        changeHealth(-2);
    }else if(e->button() == Qt::RightButton){
        changeHealth(1);
    }
}

//Function that handles the healthBar of the Castle
void Castle::changeHealth(double x)
{
    if (getHealth() + x > getMaxHealth()) {
        setHealth(getMaxHealth());
    } else if (getHealth() + x <= 0) {
        //Placeholder code for now
        setHealth(0);
        healthBar->updateBar();
    } else {
        setHealth(getHealth() + x);
        healthBar->updateBar();
    }
}
