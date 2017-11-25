#include <QTimer>

#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_wheel_visualize.hpp"
#include "ros_video_components/ros_signal_strength.hpp"
#include "gui/main_application.hpp"
Main_Application::Main_Application() {

}

void Main_Application::run() {

    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Wheel_Visualize>("bluesat.owr", 1, 0, "ROSWheelVisualize");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");
    
    //this loads the qml file we are about to create
    this->load(QUrl(QStringLiteral("qrc:/main_window.qml")));

    //Setup a timer to get the application's idle loop
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mainLoop()));
    timer->start(0);
    //set up video component

    ROS_Video_Component * video = this->rootObjects()[0]->findChild<ROS_Video_Component*>(QString("videoStream"));
    if(!video){
      printf("video component is null\n");
    }
    video->setup(&nh);

    ROS_Wheel_Visualize * wheel_visualize = this->rootObjects()[0]->findChild<ROS_Wheel_Visualize*>(QString("wheel_visualize"));
    wheel_visualize->setup(&nh);
    if(!wheel_visualize) printf("wheel visualize is null\n");
    //merge into
    ROS_Signal_Strength * signal_strength = this->rootObjects()[0]->findChild<ROS_Signal_Strength*>(QString("signal_strength"));
    signal_strength->setup(&nh);
    if(!signal_strength)  printf("signal strength is null\n");
}

void Main_Application::main_loop() {

    ros::spinOnce();

}
