#ifndef CELL_H
#define CELL_H

class Cell
{
private:
    int x, y, cost;

public:
    Cell(int x, int y, int cost);

    //getters
    int getX();
    int getY();
    int getCost();
    //setters
    void setX(int x);
    void setY(int y);
    void setCost(int c);
};

#endif // CELL_H
