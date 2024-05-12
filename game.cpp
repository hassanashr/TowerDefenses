#include "game.h"
#include <QGraphicsScene>
#include "graph.h"
#include "Boosters.h"

Game::Game()
{
    gameScene = new QGraphicsScene();
    gameGraph = new Graph();
    gameScene->setSceneRect(0, 0, 1024, 768);
    setFixedSize(1024, 768);
    setWindowTitle("Clash Of Clans");

}

void Game::createGraph()
{
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 12; j++) {
            int cost = 1;
            if (data[i][j] == 1)
                cost = 5;
            else if (data[i][j] == 2)
                cost = 50;
            Cell *newCell = new Cell(i, j, cost);
            gameGraph->addCell(newCell);
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 12; j++) {
            gameGraph->connectNeighbours(i, j);
        }
    }
}

void Game::startLevel(int l)
{
    setScene(gameScene);
    spawnedEnemy.clear();
    currentLevel = l;
    buildBoard(":/mapAssets/board1.txt");
    createGraph();
    enemySpawning = new QTimer(this);
    connect(enemySpawning, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    spawnEnemy();
    enemySpawning->start(2000);
    boosterSpawning = new QTimer(this);
    connect(boosterSpawning, SIGNAL(timeout()), this, SLOT(spawnBooster()));
    show();
}

void Game::Lost() {}

void Game::Won() {}

void Game::nextLevel() {}

int Game::getLevel()
{
    return currentLevel;
}

int Game::getMapID()
{
    return mapID;
}

double Game::getVolume()
{
    return gameVolume;
}

void Game::setMap() {}

void Game::readData(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);
    for (int i = 0; i < 16; i++) {
        QString line = in.readLine();
        QStringList numbers = line.split(" & ");
        for (int j = 0; j < 12; j++) {

            data[i][j] = numbers[j].toInt();
        }
    }
}

void Game::saveData() {}

void Game::spawnEnemy()
{
    int spawnLocation = rand() % 4;
    int x, y;
    switch (spawnLocation) {
    case 0:
        x = 0; // left side
        y = 0; // top side
        break;
    case 1:
        x = 1024; // right side
        y = 0;    // top side
        break;
    case 2:
        x = 0;   // left side
        y = 768; // bottom side
        break;
    case 3:
        x = 1024; // right side
        y = 768;  // bottom side
        break;
    }
    Enemy *enemy = new Enemy(x, y);
    gameScene->addItem(enemy);
    spawnedEnemy.append(enemy);
}

void Game::spawnBooster()
{
    //Booster* booster = new Booster(gameScene);
}

void Game::buildBoard(QString filePath)
{
    readData(filePath);
    QPixmap gridTile(":/mapAssets/Grass.png");
    gridTile = gridTile.scaled(blockPixel, blockPixel);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 12; j++) {
            mapTile[i][j] = new QGraphicsPixmapItem(gridTile);
            mapTile[i][j]->setPos(i * blockPixel, j * blockPixel);
            gameScene->addItem(mapTile[i][j]);
            if (data[i][j] == 1) {
                Wall *w = new Wall(gameScene);
                w->setPos(j * blockPixel, i * blockPixel);
                gameScene->addItem(w);
            } else if (data[i][j] == 2) {
                Tower *t = new Tower(gameScene, this);
                t->setPos(j * blockPixel, i * blockPixel);
                gameScene->addItem(t);
            } else if (data[i][j] == 3) {
                Castle *c = new Castle(gameScene, this);
                c->setPos(j * blockPixel, i * blockPixel);
            }
        }
    }
}
