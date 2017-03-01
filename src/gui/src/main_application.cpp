#include <QTimer>
#include <ros_video_components/rover_cmd_state.hpp>
#include "ros_video_components/ros_video_component.hpp"
#include "gui/main_application.hpp"

Main_Application::Main_Application() {

}

void Main_Application::run() {

    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterSingletonType<Rover_Cmd_State>("bluesat.owr.singleton", 1, 0, "RoverCmdState", &Rover_Cmd_State::qml_instance);

    // this loads the qml file we are about to create
    this->load(QUrl(QStringLiteral("qrc:/main_window.qml")));

    // Setup a timer to get the application's idle loop
    QTimer * timer  = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(main_loop()));
    timer->start(0);

    // setup the video component
    ROS_Video_Component * video = this->rootObjects()[0]->findChild<ROS_Video_Component*>(QString("videoStream"));
    video->setup(&nh);

    // setup the command state
    ((Rover_Cmd_State*)Rover_Cmd_State::qml_instance(NULL, NULL))->setup(&nh);
}

void Main_Application::main_loop() {

    ros::spinOnce();

}
