#include <QTimer>
#include <QDebug>
#include "ros_video_components/ros_video_component.hpp"
#include "gui/main_application.hpp"
#include "timer/timer.hpp"

Main_Application::Main_Application() {

}

void Main_Application::run() {

    qmlRegisterType<Timer>("bluesat.owr", 1, 0, "Timer");

    // this loads the qml file we are about to create
    this->load(QUrl(QStringLiteral("qrc:/main_window.qml")));

    // Setup a timer to get the application's idle loop
    QTimer * timer_idle  = new QTimer(this);
    connect(timer_idle, SIGNAL(timeout()), this, SLOT(main_loop()));
    timer_idle->start(0);

    // setup the video component
    //ROS_Video_Component * video = this->rootObjects()[0]->findChild<ROS_Video_Component*>(QString("videoStream"));
    //video->setup(&nh);

    Timer * stopwatch = new Timer(this);
    connect(stopwatch, SIGNAL(valueChanged()), this, SLOT(handle()));
}

void Main_Application::main_loop() {

    ros::spinOnce();
}

void Main_Application::handle() {
    qDebug() << "timer changing";
}
