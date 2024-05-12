#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "map_designer.h"
namespace Ui {
class settings;
}

class settings : public QWidget
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();
    map_designer * map_designer_w;
signals:
    void back();
    void map_design();
private slots:
    void on_back_clicked();

    void on_map_design_clicked();


private:
    Ui::settings *ui;
};

#endif // SETTINGS_H
