
#include <QTimer>
#include <QQmlEngine>
#include <qqml.h>
#include "ros_video_components/ros_general_estop.hpp"
#include <ros/ros.h>
#include <QGuiApplication>

EStopGeneral::EStopGeneral(QObject *parent) :
    QObject(parent),
    nh(NULL){

}

void EStopGeneral::setup(ros::NodeHandle *nh) {
      this->nh = nh;
}


QObject * EStopGeneral::qml_instance(QQmlEngine *engine, QJSEngine *script_engine) {
    Q_UNUSED(engine);
    Q_UNUSED(script_engine);

    if(instance == NULL) {
        instance = new EStopGeneral();
    }
    return instance;
}

// because C++ is retarded
EStopGeneral * EStopGeneral::instance = NULL;
