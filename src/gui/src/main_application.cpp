#include "gui/MainApplication.hpp"
#include <QTimer>

MainApplication::MainApplication() {

}

void MainApplication::run() {

    //this loads the qml file we are about to create
    this->load(QUrl(QStringLiteral("qrc:/window1.qml")));

    //Setup a timer to get the application's idle loop
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mainLoop()));
    timer->start(0);
}

void MainApplication::mainLoop() {
   
	qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    	qmlRegisterType<ROS_Wheel_visual>("bluesat.owr", 1, 0, "ROSWheelVisual");

    // this loads the qml file we are about to create
    this->load(QUrl(QStringLiteral("qrc:/main_window.qml")));

    // Setup a timer to get the application's idle loop
    QTimer * timer  = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(main_loop()));
    timer->start(0);

    // setup the video component
    ROS_Video_Component * video = this->rootObjects()[0]->findChild<ROS_Video_Component*>(QString("videoStream"));
    video->setup(&nh);
    ROS_Wheel_Visual * wheel_visual = this->rootObjects()[0]->findChild<ROS_Wheel_Visual*>(QString("wheel_visual"));
    wheel_visual->setup(&nh);
    
}
void Main_Application::main_loop() {

    ros::spinOnce();

}
