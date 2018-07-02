#include <QTimer>
#include <QQmlEngine>
#include <qqml.h>
#include "ros_video_components/e_stop_joints_widget.hpp"
#include <ros/ros.h>
#include <QGuiApplication>

E_Stop_Joints_Widget::E_Stop_Joints_Widget(QObject *parent) :
    QObject(parent),
    nh(NULL){

}

void E_Stop_Joints_Widget::setup(ros::NodeHandle *nh) {
      this->nh = nh;
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
    ROS_INFO("PRESS");
    //Insert any other code here
    press = new_value;
}

// because C++ is retarded
E_Stop_Joints_Widget * E_Stop_Joints_Widget::instance = NULL;
