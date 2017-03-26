#ifndef TIMER_HPP
#define TIMER_HPP

#include <QObject>
#include <QQmlApplicationEngine>
#include <QTime>
#include <ros/ros.h>

class Timer : public QQmlApplicationEngine {
    Q_OBJECT

    public:
        Timer();
        void run();

    public slots:
        void mainLoop();

    private:
        QTime::QTime t;
        ros::NodeHandle nh;

};

#endif // TIMER_HPP
