#ifndef MAP_DESIGNER_H
#define MAP_DESIGNER_H

#include <QWidget>

namespace Ui {
class map_designer;
}

class map_designer : public QWidget
{
    Q_OBJECT

public:
    explicit map_designer(QWidget *parent = nullptr);
    ~map_designer();
signals:
    void back();
private slots:
    void on_back_clicked();

private:
    Ui::map_designer *ui;
};

#endif // MAP_DESIGNER_H
