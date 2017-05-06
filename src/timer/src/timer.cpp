#include "timer/timer.hpp"

Stopwatch::Stopwatch(QQuickItem *parent) : QQuickPaintedItem(parent) {
    time.setHMS(0, 0, 0, 0);
    //msElapsed = 0;
    status = OFF;
    stopwatch = new QTimer(this);
    //stopwatch->start(INTERVAL);
    show();
    connect(stopwatch, SIGNAL(timeout()), this, SLOT(show()));

}

void Stopwatch::show() {
    //int elapsed = time.elapsed();
    //text = QString::number(elapsed);
    if (status == ON) {
        time = time.addMSecs(INTERVAL);
    }
    text = time.toString("hh:mm:ss.zzz");

    // blinking separator
    if ((time.second() % 2) == 1) {
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

void Stopwatch::keyPressEvent(QKeyEvent *k) {
    if (k->key() == Qt::Key_Space) {
        // press SPACE to pause/resume
        if (status == ON) {
            stopwatch->stop();
            qDebug() << "paused";
        } else {
            stopwatch->start(INTERVAL);
            qDebug() << "started";
        }
        status = 1 - status;  // flip status
    } else if (k->key() == Qt::Key_C) {
        // press C to clear
        stopwatch->stop();
        status = OFF;
        time.setHMS(0, 0, 0, 0);
        show();
        qDebug() << "cleared";
    }
}

void Stopwatch::paint(QPainter *painter) {
    QFont font("Sans Serif", 32, QFont::Normal);
    if (!text.isNull() && !text.isEmpty()) {
        painter->setFont(font);
        painter->drawText(QPoint(0,60), text);
    }
}
