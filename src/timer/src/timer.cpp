#include "timer/timer.hpp"

Stopwatch::Stopwatch(QQuickItem *parent) : QQuickPaintedItem(parent) {
    time.setHMS(0, 0, 0, 0);
    ms_elapsed = 0;
    status = OFF;
    stopwatch = new QTimer(this);
    //stopwatch->start(INTERVAL);
    show();
    connect(stopwatch, SIGNAL(timeout()), this, SLOT(show()));

}

void Stopwatch::show() {

    //text = QString::number(elapsed);

    if (status == ON) {
        int elapsed = time_elapsed.elapsed();
        time = time.addMSecs(elapsed - ms_elapsed);
        ms_elapsed = elapsed;
    }
    text = time.toString("hh:mm:ss.zzz");

    // blinking separator
    if ((time.second() % 2) == 1) {
        text[2] = ' ';
        text[5] = ' ';
    }

    emit valueChanged(text);
    update();
}

void Stopwatch::keyPressEvent(QKeyEvent *k) {
    if (k->key() == Qt::Key_Space) {
        // press SPACE to pause/resume
        if (status == ON) {
            stopwatch->stop();
            qDebug() << "STOP";
        } else {
            stopwatch->start(1);
            time_elapsed.start();
            ms_elapsed = 0;
            qDebug() << "START";
        }
        status = 1 - status;  // flip status
    } else if (k->key() == Qt::Key_R) {
        // press R to reset
        stopwatch->stop();
        status = OFF;
        time.setHMS(0, 0, 0, 0);
        ms_elapsed = 0;
        show();
        qDebug() << "RESET";
    }
}

void Stopwatch::paint(QPainter *painter) {
    QFont text_font("Sans Serif", 16, QFont::Normal);
    QFont title_font("Sans Serif", 10, QFont::Normal);
    if (!text.isNull() && !text.isEmpty()) {
        QRect border = QRect(0, 0, 200, 120);
        painter->setPen(Qt::green);
        painter->setFont(text_font);
        painter->drawText(border, Qt::AlignHCenter | Qt::AlignBottom, text);
        painter->setFont(title_font);
        painter->drawText(border, Qt::AlignTop, "TIMER\nSPACE to start/stop; R to reset");
        painter->drawRect(border);
    }
}
