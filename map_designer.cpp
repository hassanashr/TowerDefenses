#include "map_designer.h"
#include "ui_map_designer.h"

map_designer::map_designer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::map_designer)
{
    ui->setupUi(this);
}

map_designer::~map_designer()
{
    delete ui;
}

void map_designer::on_back_clicked()
{
    emit back();
    delete this;
}

