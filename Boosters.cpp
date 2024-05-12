#include "Boosters.h"
#include "Tower.h"
#include "worker.h"
#include "Wall.h"

Booster::Booster(QGraphicsScene* Scene) : Structure() {
    parentscene=Scene; // Adjust according to your map size

    // Load image
    QPixmap image(":/img/booster.png");
    imageItem = parentscene->addPixmap(image);



    respawnTimer = new QTimer(this);
    connect(respawnTimer, &QTimer::timeout, this, &Booster::respawnImage);
    respawnTimer->start(10000);
}

void Booster::respawnImage() {
        bool overlapped = true;
        while (overlapped) {
            // Generate random position within the scene
            int newX = QRandomGenerator::global()->bounded(0, static_cast<int>(800 - imageItem->boundingRect().width()));
            int newY = QRandomGenerator::global()->bounded(0, static_cast<int>(400 - imageItem->boundingRect().height()));
            // Check for collisions with specified item types
            overlapped = false;
            QList<QGraphicsItem*> collidingItems;
            for (auto type : {Tower::Type, Castle::Type, Enemy::Type, Worker::Type, Wall::Type}) {
                collidingItems = parentscene->items(imageItem->mapToScene(imageItem->boundingRect()).translated(newX, newY), Qt::IntersectsItemShape);
                if (!collidingItems.isEmpty()) {
                    overlapped = true;
                    break;  // Exit the loop if any collision is detected
                }
            }

            // If overlapped, try again with a new random position
            if (overlapped)
                continue;

            // Set the position if no overlap is detected
            imageItem->setPos(newX, newY);
        }
}
