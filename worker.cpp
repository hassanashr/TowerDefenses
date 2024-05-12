#include "worker.h"

Worker::Worker(int x, int y)
{

    destination = new QPointF(1*61 + 5, 1*57 + 55);
    doneHealing = true;
    doneHealingAnimation = true;
    setPixmap(QPixmap(":/img/Worker/baseSprite.png")
                  .scaled(50, 50)); //needs some refining until graphically appealing
    setPos(x, y);
    healing = 2;
    for (int i = 0; i <= 19; ++i) {
        QString filePath = ":/img/Worker/8_enemies_1_walk_" + QString("%1").arg(i, 3, 10, QChar('0')) + ".png";
        movingAnimation.append(QPixmap(filePath));

    }
    for (int i = 0; i <= 19; ++i) {
        QString filePath = ":/img/Worker/8_enemies_1_attack_" + QString("%1").arg(i, 3, 10, QChar('0'))+ ".png";
        healingAnimation.append(QPixmap(filePath));
    }
    for (int i = 0; i <= 19; ++i) {
        QString filePath = ":/img/Worker/8_enemies_1_die_" + QString("%1").arg(i, 3, 10, QChar('0'))+ ".png";
        deathAnimation.append(QPixmap(filePath));
    }

    moveTimer = new QTimer(this);
    healingTimer = new QTimer(this);
    returnTimer = new QTimer(this);
    deathTimer = new QTimer(this);
    walkTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Worker::movePath);
    connect(walkTimer, &QTimer::timeout, this, &Worker::advanceWalkFrame);
    connect(healingTimer, &QTimer::timeout, this, &Worker::advanceHealFrame);
    connect(deathTimer, &QTimer::timeout, this, &Worker::advanceDeathFrame);
    moveTimer->start(animationInterval);
}

int Worker::getHealing()
{
    return healing;
}

bool Worker::isDone()
{
    return doneHealing;
}

void Worker::setHealing(int h)
{
    healing = h;
}

//connect with Timer and stuff
void Worker::healWall(Wall *&w)
{
    while (!doneHealing) {
        //have some availibility bool or something
        setPos(x() - 3, y() - 3); //needs fine-tuning on the map. Random offsets
        moveTimer->stop();
        w->changeHealth(this->getHealing());
        if (w->getHealth() >= w->getMaxHealth()) {
            w->setHealth(w->getMaxHealth());
            doneHealing = true;
            //either here or elsewhere (probably in game class) make the queue idea
        }
    }
}

void Worker::Die()
{
    isDead = true;
    startDeathAnimation();
    QTimer::singleShot(15*animationInterval, this, SLOT(deleteWorker()));
    //game->getScene()->removeItem(this);
    //game->setDeadWorker(getDeadWorker()++);
}

void Worker::startWalkingAnimation()
{
    walkTimer->start(animationInterval);
    healingTimer->stop();
    deathTimer->stop();
}

void Worker::startHealingAnimation()
{
    walkTimer->stop();
    healingTimer->start(animationInterval);
    deathTimer->stop();
}

void Worker::startDeathAnimation()
{
    walkTimer->stop();
    healingTimer->stop();
    deathTimer->start(animationInterval);
}

void Worker::updatePixmap()
{
    //This transformation reflects the enemy horizontally
    QTransform transform;
    transform.scale(-1, 1);
    if(toRight){
        if (walkTimer->isActive()) {
            setPixmap(movingAnimation[currentWalkFrame].scaled(50, 50));
        } else if (healingTimer->isActive()) {
            setPixmap(healingAnimation[currentHealthFrame].scaled(50, 50));
        } else if (deathTimer->isActive()) {
            setPixmap(deathAnimation[currentDeathFrame].scaled(50, 50));
        }
    }else{
        if (walkTimer->isActive()) {
            setPixmap(movingAnimation[currentWalkFrame].scaled(50, 50).transformed(transform));
        } else if (healingTimer->isActive()) {
            setPixmap(healingAnimation[currentHealthFrame].scaled(50, 50).transformed(transform));
        } else if (deathTimer->isActive()) {
            setPixmap(deathAnimation[currentDeathFrame].scaled(50, 50).transformed(transform));
        }
    }
}

void Worker::movePath()
{

    if(isDead){
        return;
    }

    //Basic Movement for testing
    int stepsize = 3;
    QLineF ln(pos(), *destination);
    double theta = -ln.angle();

    double dy = stepsize * qSin(qDegreesToRadians(theta));
    double dx = stepsize * qCos(qDegreesToRadians(theta));

    //Check direction of movement, right or left
    if(dx < 0)
        toRight = false;
    else
        toRight = true;

    if(!(healingTimer->isActive()) && !(deathTimer->isActive())){
        startWalkingAnimation();
    }
    if(walkTimer->isActive()){
        setPos(pos().x()+dx, pos().y()+dy);
    }
    //stuff for A*

    QList<QGraphicsItem *> collided_items = collidingItems();
    for (auto item : collided_items) {
        if(typeid(*item) == typeid(Wall)){
            startHealingAnimation();
            if(dynamic_cast<Wall*>(item)->isDamaged()){

                if(doneHealingAnimation){
                    dynamic_cast<Wall*>(item)->changeHealth(healing);
                    doneHealing = false;
                    doneHealingAnimation = false;
                }

                QTimer::singleShot(1200, this, SLOT(cooldownTime()));
            }else{
                doneHealing = true;
                startWalkingAnimation();
            }
        }
    }
}

void Worker::advanceWalkFrame()
{
    currentWalkFrame = (currentWalkFrame + 1) % movingAnimation.size();
    updatePixmap();
}

void Worker::advanceHealFrame()
{
    currentHealthFrame = (currentHealthFrame + 1) % healingAnimation.size();
    updatePixmap();
}

void Worker::advanceDeathFrame()
{
    currentDeathFrame = (currentDeathFrame + 1) % deathAnimation.size();
    updatePixmap();
}

void Worker::cooldownTime()
{
    doneHealingAnimation = true;
}

void Worker::deleteWorker()
{
    delete this;
}
