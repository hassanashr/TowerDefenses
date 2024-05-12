#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
class CloseButton: public QObject, public QGraphicsPixmapItem
{
public:
    CloseButton(QWidget* parent = 0);
    QWidget* original;

signals:
    void back();
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
};

#endif // CLOSEBUTTON_H
