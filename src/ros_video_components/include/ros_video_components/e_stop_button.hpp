#ifndef E_STOP_BUTTON_HPP
#define E_STOP_BUTTON_HPP

//QT
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QQmlExtensionPlugin>

#include <ros/ros.h>

class E_Stop_Button : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(E_Stop_Button)


  public:
        E_Stop_Button(QObject *parent = 0);
        void setup(ros::NodeHandle * nh);


    //make it a singleton
    static QObject * qml_instance(QQmlEngine * engine, QJSEngine * scriptEngine);
        static E_Stop_Button * instance;
    signals:


  public slots:

    private:
        ros::NodeHandle * nh;
};


#endif // E_STOP_BUTTON_HPP
