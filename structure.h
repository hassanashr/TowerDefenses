#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QPair>


class Structure: public QObject, public QGraphicsPixmapItem
{
public:
    Structure();
    //getters
    double getHealth();
    double getMaxHealth();
    int getCost();
    int getType();
    int getX();
    int getY();

    void setPosition(int, int);
    void setType(int t);
    void setHealth(double h);
    void setMaxHealth(double h);
    void setCost(double c);
    bool isDamaged();
    virtual void changeHealth(int);

    //HealthBar* healthBar;
    //virtual void updateHealthBar() = 0;

    //Since I cannot use Game as it has a Structures array, I use the QGraphicsScene to add elements that other structures add
    QGraphicsScene* parent;

protected:
    //position
    int xx, yy;

    //Type
    int type;

    double health;

    double maxHealth;
    double costOfWalk;
};


#endif // STRUCTURE_H
