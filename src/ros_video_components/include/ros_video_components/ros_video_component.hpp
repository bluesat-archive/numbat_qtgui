/*
 * Date Started: 25/12/16
 * Original Author: Harry J.E Day
 * Editors:
 * Purpose: Widget that renders a video from a ROS sensor_msgs/Image stream.
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2018
 */
#ifndef ROS_VIDEO_COMPONENT_H
#define ROS_VIDEO_COMPONENT_H

//QT
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

#include <QObject>

//ROS
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
//#include "owr_messages/activeCameras.h"

class ROS_Video_Component : public QQuickPaintedItem {
    //make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Video_Component(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);

    protected:

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();


    private:
        void receive_image(const sensor_msgs::Image::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        image_transport::ImageTransport * img_trans;
        image_transport::Subscriber image_sub;
        QString topic_value;
        bool ros_ready;

        // Used for buffering the image
        QImage * current_image;
        uchar * current_buffer;
};

#endif // ROS_VIDEO_COMPONENT_H
