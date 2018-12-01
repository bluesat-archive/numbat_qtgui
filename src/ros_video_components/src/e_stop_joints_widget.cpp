#include <QTimer>
#include <QQmlEngine>
#include <qqml.h>
#include "ros_video_components/e_stop_joints_widget.hpp"
#include <ros/ros.h>
#include <QGuiApplication>

E_Stop_Joints_Widget::E_Stop_Joints_Widget(QObject *parent) :
    QObject(parent){

}

void E_Stop_Joints_Widget::setup(ros::NodeHandle *nh) {
}


QObject * E_Stop_Joints_Widget::qml_instance(QQmlEngine *engine, QJSEngine *script_engine) {
    Q_UNUSED(engine);
    Q_UNUSED(script_engine);

    if(instance == NULL) {
        instance = new E_Stop_Joints_Widget();
    }
    return instance;
}

bool E_Stop_Joints_Widget::getPress() const {
    return press;
}

void E_Stop_Joints_Widget::setPress(const bool &new_value) {
   //ROS_INFO("PRESS");
    //Insert any other code here

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
E_Stop_Joints_Widget * E_Stop_Joints_Widget::instance = NULL;
