/*
 * Date Started: 25/12/16
 * Original Author: Harry J.E Day
 * Editors:
 * Purpose: Widget that renders a video from a ROS sensor_msgs/Image stream.
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2018
 */
#ifndef ROS_USB_RESET_H
#define ROS_USB_RESET_H

//QT
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

#include <QObject>

//ROS
#include <ros/ros.h>
#include "std_msgs/String.h"

class ROS_Usb_Reset : public QQuickPaintedItem {
    //make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Usb_Reset(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);

    protected:

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();


    private:
        void receive_msg(const std_msgs::String::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Subscriber usb_sub;
        QString topic_value;
        bool ros_ready;

        // Used for buffering the image
        std::string devices;
};

#endif // ROS_USB_RESET_H
