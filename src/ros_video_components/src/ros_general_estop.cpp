/**
* Date Started: 25/05/2018
* Original Author: Yubai Jiang
* ROS Node Name: ros_general_estop
* ROS Package: ros_video_components (to be changed later)
* Purpose: Node that send a stop message when a gui e-stop button is pressed
*/

#include <QTimer>
#include <QQmlEngine>
#include <qqml.h>
#include "ros_video_components/ros_general_estop.hpp"
#include <ros/ros.h>
#include <QGuiApplication>

E_Stop_Button::E_Stop_Button(QObject *parent) :
    QObject(parent){

}


void E_Stop_Button::setup(ros::NodeHandle *nh) {

}


QObject * E_Stop_Button::qml_instance(QQmlEngine *engine, QJSEngine *script_engine) {
    Q_UNUSED(engine);
    Q_UNUSED(script_engine);

    if(instance == NULL) {
        instance = new E_Stop_Button();
    }
    return instance;
}

bool E_Stop_Button::getPress() const {
    return press;
}

void E_Stop_Button::setPress(const bool &new_value) {

    ros::NodeHandle nh;
    pub = nh.advertise<std_msgs::Float64>("/e_stop/test", 1, true);

    std_msgs::Float64 msg;

    if(new_value)
    {
      msg.data = 1000;
      ROS_INFO("EMERGENCY STOP");
    }
    else
    {
      msg.data = 10;
      ROS_INFO("OK TO RESUME");
    }

    pub.publish(msg);

    press = new_value;
}

// because C++ is retarded
E_Stop_Button * E_Stop_Button::instance = NULL;
