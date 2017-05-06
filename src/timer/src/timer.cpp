#include "timer/timer.hpp"

Stopwatch::Stopwatch(QQuickItem *parent) : QQuickPaintedItem(parent) {
    time.setHMS(0, 0, 0, 0);
    //msElapsed = 0;
    QTimer *stopwatch = new QTimer(this);
    stopwatch->start(INTERVAL);
    connect(stopwatch, SIGNAL(timeout()), this, SLOT(show()));
}

void Stopwatch::show() {
    //int elapsed = time.elapsed();
    //text = QString::number(elapsed);
    time = time.addMSecs(INTERVAL);
    text = time.toString("hh:mm:ss.zzz");

    // blinking separator
    if ((time.second() % 2) == 0) {
        text[2] = ' ';
        text[5] = ' ';
    }

    emit valueChanged(text);
    update();
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

void Stopwatch::paint(QPainter *painter) {
    QFont font("Sans Serif", 32, QFont::Normal);
    if (!text.isNull() && !text.isEmpty()) {
        painter->setFont(font);
        painter->drawText(QPoint(0,60), text);
    }
}
