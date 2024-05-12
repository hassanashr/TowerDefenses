#ifndef WORKER_H
#define WORKER_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <Wall.h>
#include <QPointF>

class Wall;

class Worker : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    int healing;
    double currSpeed;

    //Timers and their Pixmaps
    QTimer *moveTimer;
    QTimer *walkTimer;
    QTimer *healingTimer;
    QTimer *deathTimer;
    QTimer *returnTimer;
    QList<QPixmap> movingAnimation;
    QList<QPixmap> healingAnimation;
    QList<QPixmap> deathAnimation;
    int currentWalkFrame = 0;
    int currentHealthFrame = 0;
    int currentDeathFrame = 0;
    int animationInterval = 100;
    bool doneHealing;
    bool doneHealingAnimation;
    bool toRight;
    bool isDead = false;

    //Location to go
    QPointF* destination;

public:
    Worker(int, int);

    //getters
    int getHealing();
    bool isDone();

    //setters
    void setHealing(int h);
    void decreaseHealth(int h);
    void setDestination(QPointF*);

    //functionalities
    void healWall(Wall *&);
    void Die();

    //Update animation
    void startWalkingAnimation();
    void startHealingAnimation();
    void startDeathAnimation();
    void updatePixmap();

public slots:
    void movePath();
    void advanceWalkFrame();
    void advanceHealFrame();
    void advanceDeathFrame();
    void cooldownTime();
    void deleteWorker();
};

#endif // WORKER_H
