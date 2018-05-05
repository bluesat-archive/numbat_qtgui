#include <QTimer>
#include <QQmlEngine>
#include <qqml.h>
#include "ros_video_components/e_stop_button.hpp"
#include <ros/ros.h>
#include <QGuiApplication>

E_Stop_Button::E_Stop_Button(QObject *parent) :
    QObject(parent),
    nh(NULL){

}

void E_Stop_Button::setup(ros::NodeHandle *nh) {
      this->nh = nh;
}


QObject * E_Stop_Button::qml_instance(QQmlEngine *engine, QJSEngine *script_engine) {
    Q_UNUSED(engine);
    Q_UNUSED(script_engine);

    if(instance == NULL) {
        instance = new E_Stop_Button();
    }
    return instance;
}

// because C++ is retarded
E_Stop_Button * E_Stop_Button::instance = NULL;
