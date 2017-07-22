//#include "Sensor_Motor_Trim/MainApplication.hpp"
#include <QTimer>
#include <QQmlEngine>
#include <qqml.h>
#include "ros_video_components/sensor_motor_trim.hpp"
#include <ros/ros.h>
#include <QGuiApplication>

#define MOTOR_LEFT_FRONT 0

//Functions to make sure the Sensor_Motor_Trim QObject runs correctly
Sensor_Motor_Trim::Sensor_Motor_Trim(QObject *parent) :
    QObject(parent),
    nh(NULL){

}

void Sensor_Motor_Trim::setup(ros::NodeHandle *nh) {
      this->nh = nh;
}

int Sensor_Motor_Trim::getIndex() const {
    return index;
}

void Sensor_Motor_Trim::setIndex(const int &new_value) {
    index = new_value;
}

bool Sensor_Motor_Trim::getPress() const {
    return press;
}

void Sensor_Motor_Trim::setPress(const bool &new_value) {
    ROS_INFO("PRESS");
    ROS_INFO("Index is: %d", getIndex());
    ROS_INFO("Value is: %lf", getValue());
    //Insert code here
    press = new_value;
}

double Sensor_Motor_Trim::getValue() const {
    return value;
}

void Sensor_Motor_Trim::setValue(const double &new_value) {
    value = new_value;
}

QObject * Sensor_Motor_Trim::qml_instance(QQmlEngine *engine, QJSEngine *script_engine) {
    Q_UNUSED(engine);
    Q_UNUSED(script_engine);

    if(instance == NULL) {
        instance = new Sensor_Motor_Trim();
    }
    return instance;
}

// because C++ is retarded
Sensor_Motor_Trim * Sensor_Motor_Trim ::instance = NULL;
