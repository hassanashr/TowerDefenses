#ifndef GAME_H
#define GAME_H
#include <QFile>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextStream>
#include <QTimer>
#include <QWidget>
#include <castle.h>
#include <cell.h>
#include <enemy.h>
#include <graph.h>
#include <tower.h>
#include <wall.h>
class Enemy;
class Game : public QGraphicsView
{
public:
    Game();
    Graph *gameGraph;
    QGraphicsScene *gameScene;

    void buildBoard(QString filePath);
    void readData(QString filePath);
    void createGraph();
    void startLevel(int);
    void Lost();
    void Won();
    void nextLevel();

    //getters
    int getLevel();
    int getMapID();
    double getVolume();

    //setters
    void setMap();

private:
    QGraphicsView *gameView;
    int data[16][12];
    QGraphicsPixmapItem *mapTile[16][12];
    int blockPixel = 64;
    int currentLevel;
    int mapID;
    double gameVolume;
    void makeGraph();
    void readData();
    void saveData();
    void makeBoard();

    QTimer *enemySpawning;
    QTimer *boosterSpawning;

    QList<Enemy *> spawnedEnemy;
    QList<Wall *> damagedWall;

public slots:
    void spawnEnemy();
};

#endif // GAME_H
