#include "cell.h"

Cell::Cell(int x, int y, int cost)
    : x(x)
    , y(y)
    , cost(cost)
{}

int Cell::getX()
{
    return x;
}

int Cell::getY()
{
    return y;
}

int Cell::getCost()
{
    return cost;
}

void Cell::setX(int x)
{
    this->x = x;
}
void Cell::setY(int y)
{
    this->y = y;
}
void Cell::setCost(int c)
{
    this->cost = c;
}
