/*
 * Date Started: 11/02/17
 * Original Author: Sajid Anower
 * Editors:
 * Purpose: Widget to display signal strength of the antenna
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2017
 */
#ifndef ROS_SIGNAL_STRENGTH_H
#define ROS_SIGNAL_STRENGTH_H

// QT
#include <QQuickPaintedItem>
#include <QPainter>

// ROS
#include <ros/ros.h>
#include <std_msgs/Float32.h>


class ROS_Signal_Strength : public QQuickPaintedItem {
    // make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Signal_Strength(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);

        // getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();

    private:
        void receive_signal(const std_msgs::Float32::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Subscriber signal_sub;
        QString topic_value;
        bool ros_ready;

        int data; // the signal strength in decibels
};

#endif // ROS_SIGNAL_STRENGTH_H
