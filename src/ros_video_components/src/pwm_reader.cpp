clude <QTimer>
#include <QQmlEngine>
#include <qqml.h>
#include "ros_video_components/example_widget.hpp"
#include <ros/ros.h>
#include <QGuiApplication>

PWM_Reader::PWM_Reader(QObject *parent) :
    QObject(parent),
    nh(NULL){

}

void PWM_Reader::setup(ros::NodeHandle *nh) {
      this->nh = nh;
}


QObject * PWM_Reader::qml_instance(QQmlEngine *engine, QJSEngine *script_engine) {
    Q_UNUSED(engine);
    Q_UNUSED(script_engine);

    if(instance == NULL) {
        instance = new PWM_Reader();
    }
    return instance;
}

// because C++ is retarded
PWM_Reader * PWM_Reader::instance = NULL;
