#include "healthbar.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QDebug>
HealthBar::HealthBar(Structure* parent, int w, int h, int xPos, int yPos, int stroke) {
    this->parent = parent;
    xPosition = xPos;
    yPosition = yPos;
    borderStroke = stroke;
    //The black bar for borders
    blackBar = new QGraphicsRectItem(xPosition, yPosition, w, h);
    blackBar->setBrush(QBrush(Qt::black));
    parent->parent->addItem(blackBar);
    //White bar for empty health
    whiteBar = new QGraphicsRectItem(xPosition+borderStroke, yPosition+borderStroke, w-2*borderStroke, h-2*borderStroke);
    whiteBar->setBrush(QBrush(Qt::white));
    parent->parent->addItem(whiteBar);
    //Red bar for remaining health
    redBar = new QGraphicsRectItem(xPosition+borderStroke, yPosition+borderStroke, w-2*borderStroke, h-2*borderStroke);
    redBar->setBrush(QBrush(Qt::red));
    parent->parent->addItem(redBar);
    width = w;
    height = h;
}

HealthBar::~HealthBar()
{
    delete blackBar;
    delete whiteBar;
    delete redBar;
}

void HealthBar::updateBar(){
    redBar->setRect(xPosition + borderStroke,
                    yPosition + borderStroke,
                    parent->getHealth() / parent->getMaxHealth() * (width - 2 * borderStroke),
                    height - 2 * borderStroke);
}

