#include "mainwindow.h"
#include "game.h"
#include "map_designer.h"
#include "settings.h"
#include "ui_mainwindow.h"

extern Game *game;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::won(){
    win_w = new win();
    setCentralWidget(win_w);
//add connections
}
void MainWindow::lost(){
    lose_w = new lose();
    setCentralWidget(lose_w);
    //add connections
}
void MainWindow::on_start_clicked()
{
    game = new Game();
    setCentralWidget(game);
    QObject::connect(game,&Game::win,this,&MainWindow::won);
    QObject::connect(game,&Game::lose,this,&MainWindow::lost);
    game->startLevel(1);
    qDebug() << "After start.";
}

void MainWindow::on_settings_clicked()
{
    settings_w = new settings();
    QObject::connect(settings_w,&settings::back,this,&MainWindow::reset);
    QObject::connect(settings_w,&settings::map_design,this,&MainWindow::map_design);
    setCentralWidget(settings_w);
}
void MainWindow::back_to_settings(){
    setCentralWidget(settings_w);
}
void MainWindow::map_design(){
    settings_w->map_designer_w = new map_designer;
    QObject::connect(settings_w->map_designer_w,&map_designer::back,this,&MainWindow::back_to_settings);
    setCentralWidget(settings_w->map_designer_w);
}
void MainWindow::reset(){
    ui->setupUi(this);
}

void MainWindow::on_exit_clicked()
{
    this->close();
}
