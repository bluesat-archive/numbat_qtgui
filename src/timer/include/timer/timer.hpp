#ifndef TIMER_HPP
#define TIMER_HPP

#include <QObject>
#include <ros/ros.h>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QQuickPaintedItem>

#define ON 1
#define OFF 0

class Stopwatch : public QQuickPaintedItem {
    Q_OBJECT
    public:
        Stopwatch(QQuickItem *parent = 0);
        void paint(QPainter *painter);
        void keyPressEvent(QKeyEvent *k);
        //void run();
        //void setup(ros::NodeHandle * nh);

    signals:
        void valueChanged(QString text);

    private slots:
        void show();

    private:
        int ms_elapsed;
        QTime time;
        QTime time_elapsed;
        QString text;
        QTimer *stopwatch;
        int status;
        //ros::NodeHandle nh;
        //QString format(int milisecs);
};

#endif // TIMER_HPP
