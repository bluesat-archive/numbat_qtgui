#include <QTimer>
#include <QDebug>
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_signal_strength.hpp"
#include "ros_video_components/ros_voltage_meter.hpp"
#include "ros_video_components/ros_camera_switching.hpp"
#include "ros_video_components/ros_timer.hpp"
#include "ros_video_components/ros_joystick_listener.hpp"
#include "ros_video_components/ros_drive_mode.hpp"
#include "gui/main_application.hpp"
#include "usb_reset/ros_usb_reset.hpp"

Main_Application::Main_Application() {}

void Main_Application::run() {
    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");
    qmlRegisterType<ROS_Voltage_Meter>("bluesat.owr", 1, 0, "ROSVoltageMeter");
    qmlRegisterType<ROS_Camera_Switching>("bluesat.owr", 1, 0, "ROSCameraSwitching");
    qmlRegisterType<ROSTimer>("bluesat.owr", 1, 0, "ROSTimer");
    qmlRegisterType<Ros_Joystick_Listener>("bluesat.owr", 1, 0, "ROSJoystickListener");
    qmlRegisterType<Ros_Drive_Mode>("bluesat.owr", 1, 0, "ROSDriveMode");
    qmlRegisterType<ROS_Usb_Reset>("bluesat.owr", 1, 0, "ROSUsbReset");

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

    ROS_Voltage_Meter * voltage_meter = this->rootObjects()[0]->findChild<ROS_Voltage_Meter*>(QString("voltage_meter"));
    voltage_meter->setup(&nh);

    ROS_Camera_Switching * camera_switching = this->rootObjects()[0]->findChild<ROS_Camera_Switching*>(QString("camera_switching"));
    camera_switching->setup(&nh);

    Ros_Joystick_Listener * bot_joystick = this->rootObjects()[0]->findChild<Ros_Joystick_Listener*>(QString("bot_joystick"));
    bot_joystick->setup(&nh);

    Ros_Drive_Mode * drive_mode = this->rootObjects()[0]->findChild<Ros_Drive_Mode*>(QString("drive_mode"));
    drive_mode->setup(&nh);

    //this->rootContext passes the root context of main_window.qml
    ROS_Usb_Reset * usb_reset = this->rootObjects()[0]->findChild<ROS_Usb_Reset*>(QString("usb_reset"));
    usb_reset->setup(&nh, this->rootContext());

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
