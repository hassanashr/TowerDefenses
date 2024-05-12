
#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QGraphicsTextItem>
#include <QTimer>
#include "game.h"

class TimerWidget : public QGraphicsTextItem {
    Q_OBJECT
public:
    TimerWidget(Game *parent = nullptr);
    Game* parentGame;
    void startTimer();
    void stopTimer();

private slots:
    void updateTime();

private:
    int timeRemaining;
    QTimer *timer;
};

#endif // TIMERWIDGET_H
