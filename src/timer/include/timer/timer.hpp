#ifndef TIMER_HPP
#define TIMER_HPP

#include <QObject>
#include <ros/ros.h>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QQuickPaintedItem>

class Timer : public QQuickPaintedItem {
    Q_OBJECT
    public:
        Timer(QQuickItem *parent = 0);
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
