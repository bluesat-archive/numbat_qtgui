#include "ros_video_components/ros_timer.hpp"

ROSTimer::ROSTimer(QQuickItem *parent) : QQuickPaintedItem(parent) {
    time.setHMS(0, 0, 0, 0);
    ms_elapsed = 0;
    status = OFF;
    stopwatch = new QTimer(this);
    //stopwatch->start(INTERVAL);
    show();
    connect(stopwatch, SIGNAL(timeout()), this, SLOT(show()));

}

void ROSTimer::show() {

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

void ROSTimer::keyPressEvent(QKeyEvent *k) {
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

void ROSTimer::paint(QPainter *painter) {

    // set font
    QFont text_font("Sans Serif", 10, QFont::Bold);
    QFont title_font("Sans Serif", 6, QFont::Bold);

    if (!text.isNull() && !text.isEmpty()) {
        QRect border = QRect(0, 0, 140, 50);
        QRect text_bound = QRect(5, 5, 130, 40);

        // draw background
        QBrush brush(Qt::gray, Qt::SolidPattern);
        painter->fillRect(border, brush);
        painter->setPen(Qt::blue);
        painter->drawRect(border);

        // draw text
        painter->setFont(text_font);
        painter->drawText(text_bound, Qt::AlignHCenter | Qt::AlignBottom, text);
        painter->setFont(title_font);
        painter->drawText(text_bound, Qt::AlignTop, "TIMER\nSPACE=start/stop  R=reset");
    }
}
