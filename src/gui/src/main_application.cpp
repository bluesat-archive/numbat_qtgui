#include <QTimer>
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_signal_strength.hpp"
#include "ros_video_components/ros_driving_mode_switching.hpp"
#include "gui/main_application.hpp"



Main_Application::Main_Application() {

}

void Main_Application::run() {

    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");
    qmlRegisterType<ROS_Driving_Mode_Switching>("bluesat.owr", 1, 0, "ROSDrivingModeSwitching");


    // this loads the qml file we are about to create
    this->load(QUrl(QStringLiteral("qrc:/main_window.qml")));

    // Setup a timer to get the application's idle loop
    QTimer * timer  = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(main_loop()));
    timer->start(0);

    // setup the video component
    ROS_Video_Component * video = this->rootObjects()[0]->findChild<ROS_Video_Component*>(QString("videoStream"));
    video->setup(&nh);
    ROS_Signal_Strength * signal_strength = this->rootObjects()[0]->findChild<ROS_Signal_Strength*>(QString("signal_strength"));
    signal_strength->setup(&nh);
    ROS_Driving_Mode_Switching* driving_mode_switching = this->rootObjects()[0]->findChild<ROS_Driving_Mode_Switching*>(QString("driving_mode_switching"));
    driving_mode_switching ->setup(&nh);
}

void Main_Application::main_loop() {

    ros::spinOnce();

}
