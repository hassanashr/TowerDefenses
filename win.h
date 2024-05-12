#ifndef WIN_H
#define WIN_H

#include <QWidget>

namespace Ui {
class win;
}

class win : public QWidget
{
    Q_OBJECT

public:
    explicit win(QWidget *parent = nullptr);
    ~win();

private:
    Ui::win *ui;
};

#endif // WIN_H
