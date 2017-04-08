#include "timer/timer.hpp"

Timer::Timer(QQuickItem *parent) : QQuickPaintedItem(parent) {
    time.setHMS(0, 0, 0, 0);
    //msElapsed = 0;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(show()));
    timer->start(1);
    show();
}

void Timer::show() {
    time = time.addMSecs(1);
    text = time.toString("hh:mm:ss.zzz");
    if ((time.second() % 2) == 0) {
        text[2] = ' ';
        text[5] = ' ';
    }
    emit valueChanged(text);
/*
    time->start();
    QString text;
    while (1) {
        msElapsed = time->elapsed();
        text = QString::number(msElapsed);
        emit changed();
    }
*/
}

void Timer::paint(QPainter *painter) {
    if (!text.isNull() && !text.isEmpty()) {
        painter->drawText(QPoint(0,0), text);
    }
}
