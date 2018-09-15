#ifndef USB_RESET_HPP
#define USB_RESET_HPP

//QT
#include <QQuickPaintedItem>
#include <QPainter>

//ROS
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include "std_msgs/String.h"
#include <string.h>


class  ROS_Usb_Reset: public QQuickPaintedItem {
    //make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Usb_Reset(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();

    private:
        void receive_signal(const std_msgs::String::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Subscriber signal_sub;
        QString topic_value;
        bool ros_ready;

    std::string devices; //usb devices
};



#endif // USB_RESET_HPP
