#ifndef TIMER_HPP
#define TIMER_HPP

#include <QObject>
#include <QWidget>
#include <ros/ros.h>
#include <QTime>
#include <QTimer>
#include <QLCDNumber>

class Timer : public QLCDNumber {
    Q_OBJECT
    public:
        Timer(QWidget *parent = 0);
        //void run();
        //void setup(ros::NodeHandle * nh);

    signals:
        void valueChanged();

    private slots:
        void show();

    private:
        //int msElapsed;
        QTime *time;
        //ros::NodeHandle nh;
        //QString format(int milisecs);
};

#endif // TIMER_HPP
