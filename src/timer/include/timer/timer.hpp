#ifndef TIMER_HPP
#define TIMER_HPP

#include <QObject>
#include <ros/ros.h>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QQuickPaintedItem>

#define INTERVAL 21

class Stopwatch : public QQuickPaintedItem {
    Q_OBJECT
    public:
        Stopwatch(QQuickItem *parent = 0);
        void paint(QPainter *painter);
        //void run();
        //void setup(ros::NodeHandle * nh);

    signals:
        void valueChanged(QString text);

    private slots:
        void show();

    public:
        //int msElapsed;
        QTime time;
        QString text;
        //ros::NodeHandle nh;
        //QString format(int milisecs);
};

#endif // TIMER_HPP
