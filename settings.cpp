#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::settings)
{
    ui->setupUi(this);
}

settings::~settings()
{
    delete ui;
}

void settings::on_back_clicked()
{
    emit back();
    delete this;
}


void settings::on_map_design_clicked()
{
    map_designer_w = new map_designer;
    emit map_design();
}


