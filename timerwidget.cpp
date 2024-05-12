#include "timerwidget.h"
#include <QFont>
#include <QDebug>
TimerWidget::TimerWidget(Game *parent) : QGraphicsTextItem(0), timeRemaining(5 * 60) {
    setPlainText("5:00");
    parentGame = parent;
    QFont font("Arial", 16);
    setFont(font);
    setDefaultTextColor(Qt::black);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TimerWidget::updateTime);
}

void TimerWidget::startTimer() {
    timeRemaining = 200;
    updateTime();
    timer->start(1000);
}

void TimerWidget::stopTimer() {
    timer->stop();
}

void TimerWidget::updateTime() {
    if (timeRemaining > 0) {
        timeRemaining -= 1;
        int minutes = timeRemaining / 60;
        int seconds = timeRemaining % 60;
        setPlainText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
    } else {
        setPlainText("Time's up!");
        timer->stop();
    }
}
