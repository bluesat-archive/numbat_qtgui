#include <QTimer>
#include <QDebug>
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_signal_strength.hpp"
#include "gui/main_application.hpp"
#include "timer/timer.hpp"

Main_Application::Main_Application() {

}

void Main_Application::run() {

    qmlRegisterType<Stopwatch>("bluesat.owr", 1, 0, "Stopwatch");
    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");

    // this loads the qml file we are about to create
    this->load(QUrl(QStringLiteral("qrc:/main_window.qml")));

    // Setup a timer to get the application's idle loop
    QTimer * timer_idle  = new QTimer(this);
    connect(timer_idle, SIGNAL(timeout()), this, SLOT(main_loop()));
    timer_idle->start(0);

    // setup the video component
    ROS_Video_Component * video = this->rootObjects()[0]->findChild<ROS_Video_Component*>(QString("videoStream"));
    video->setup(&nh);

    ROS_Signal_Strength * signal_strength = this->rootObjects()[0]->findChild<ROS_Signal_Strength*>(QString("signal_strength"));
    signal_strength->setup(&nh);

    // setup the stopwatch
    Stopwatch * stopwatch = this->rootObjects()[0]->findChild<Stopwatch *>(QString("timerDisplay"));
    connect(stopwatch, SIGNAL(valueChanged(QString)), this, SLOT(handle(QString)));
}

void Main_Application::main_loop() {

    ros::spinOnce();
}

void Main_Application::handle(QString str) {
    qDebug() << str;
}
