#include <QTimer>
#include <QDebug>
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_wheel_visualize.hpp"
#include "ros_video_components/ros_signal_strength.hpp"
#include "ros_video_components/ros_camera_switching.hpp"
#include "ros_video_components/ros_timer.hpp"
#include "ros_video_components/ros_joystick_listener.hpp"
#include "gui/main_application.hpp"

Main_Application::Main_Application() {

}

void Main_Application::run() {

    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Wheel_Visualize>("bluesat.owr", 1, 0, "ROSWheelVisualize");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");
    qmlRegisterType<ROS_Camera_Switching>("bluesat.owr", 1, 0, "ROSCameraSwitching");
    qmlRegisterType<ROSTimer>("bluesat.owr", 1, 0, "ROSTimer");
    qmlRegisterType<Ros_Joystick_Listener>("bluesat.owr", 1, 0, "ROSJoystickListener");

    // this loads the qml file we are about to create
    this->load(QUrl(QStringLiteral("qrc:/main_window.qml")));

    // Setup a timer to get the application's idle loop
    QTimer * timer_idle  = new QTimer(this);
    connect(timer_idle, SIGNAL(timeout()), this, SLOT(main_loop()));
    timer_idle->start(0);

    // setup the video component
    ROS_Video_Component * video = this->rootObjects()[0]->findChild<ROS_Video_Component*>(QString("videoStream"));
    video->setup(&nh);

    ROS_Wheel_Visualize * wheel_visualize = this->rootObjects()[0]->findChild<ROS_Wheel_Visualize*>(QString("wheel_visualize"));
    wheel_visualize->setup(&nh);
    if(!wheel_visualize) printf("wheel visualize is null\n");
    //merge into
    ROS_Signal_Strength * signal_strength = this->rootObjects()[0]->findChild<ROS_Signal_Strength*>(QString("signal_strength"));
    signal_strength->setup(&nh);

    ROS_Camera_Switching * camera_switching = this->rootObjects()[0]->findChild<ROS_Camera_Switching*>(QString("camera_switching"));
    camera_switching->setup(&nh);

    Ros_Joystick_Listener * bot_joystick = this->rootObjects()[0]->findChild<Ros_Joystick_Listener*>(QString("bot_joystick"));
    bot_joystick->setup(&nh);


    // setup the timer
    ROSTimer * stopwatch = this->rootObjects()[0]->findChild<ROSTimer *>(QString("timerDisplay"));
    // the following code section is for debugging
    /*
    if (stopwatch != NULL) {
        connect(stopwatch, SIGNAL(valueChanged(QString)), this, SLOT(handle(QString)));
    }
    */
}

void Main_Application::main_loop() {

    ros::spinOnce();
}

void Main_Application::handle(QString str) {
    qDebug() << str;
}
