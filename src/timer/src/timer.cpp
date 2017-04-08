#include "timer/timer.hpp"

Timer::Timer(QWidget *parent) : QLCDNumber(parent) {
    setSegmentStyle(Filled);
    time = new QTime(0, 0);
    //msElapsed = 0;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(show()));
    timer->start(1);
    show();
    time->start();
}

void Timer::show() {
    time->addMSecs(1);
    QString text = time->toString("hh:mm:ss.z");
    if ((time->second() % 2) == 0) {
        text[2] = ' ';
        text[5] = ' ';
    }
    display(text);
    emit valueChanged();
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
