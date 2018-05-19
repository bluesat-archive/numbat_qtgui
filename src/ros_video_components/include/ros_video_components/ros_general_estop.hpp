/**
* Date Started: 25/05/2018
* Original Author: Yubai Jiang
* ROS Node Name: E_Stop_Button
* ROS Package: ros_video_components (to be changed later)
* Purpose: Node that send a stop message when a gui e-stop button is pressed
*/

#ifndef E_STOP_BUTTON_HPP
#define E_STOP_BUTTON_HPP

//QT
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QQmlExtensionPlugin>

#include <ros/ros.h>
#include <std_msgs/Float64.h>

class E_Stop_Button : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(E_Stop_Button)
    Q_PROPERTY(bool press READ getPress WRITE setPress NOTIFY Pressed)


  public:
        E_Stop_Button(QObject *parent = 0);
        void setup(ros::NodeHandle * nh);
        bool getPress() const;
        void setPress(const bool &new_value);


    //make it a singleton
    static QObject * qml_instance(QQmlEngine * engine, QJSEngine * scriptEngine);
    static E_Stop_Button * instance;

  signals:
    void Pressed();


  public slots:

  private:
    ros::Publisher pub;
    bool press;
};


#endif // E_Stop_Button_HPP
