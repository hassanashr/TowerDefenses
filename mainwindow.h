#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "map_designer.h"
#include "game.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();

    void on_settings_clicked();

    void reset();

    void map_design();

    void back_to_settings();
    void on_exit_clicked();

private:
    Ui::MainWindow *ui;
    Game * game_w;
    settings * settings_w;
};

#endif // MAINWINDOW_H
