#include <QTimer>
#include <QDebug>
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_signal_strength.hpp"
#include "ros_video_components/ros_coord_bearing.hpp"
#include "ros_video_components/ros_timer.hpp"
#include "gui/main_application.hpp"

Main_Application::Main_Application() {

}

void Main_Application::run() {

    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");
    qmlRegisterType<ROSCoordBearing>("bluesat.owr", 1, 0, "ROSCoordBearing");

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
    ROSTimer * stopwatch = this->rootObjects()[0]->findChild<ROSTimer *>(QString("timerDisplay"));
    connect(stopwatch, SIGNAL(valueChanged(QString)), this, SLOT(handle(QString)));

    // coordinates and bearing readouts
    ROSCoordBearing * cbreads = this->rootObjects()[0]->findChild<ROSCoordBearing *>(QString("coord_bearing"));
}

void Main_Application::main_loop() {

    ros::spinOnce();
}

void Main_Application::handle(QString str) {
    qDebug() << str;
}
