/*
 * Date Started: 8/09/18
 * Original Author: Sajid Ibne Anower
 * Editors:
 * Purpose: Widget to display voltage of the batteries
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2017, 2018
 */
#ifndef ROS_VOLTAGE_METER_H
#define ROS_VOLTAGE_METER_H

// QT
#include <QQuickPaintedItem>
#include <QPainter>

// ROS
#include <ros/ros.h>
#include <std_msgs/Float32.h>

class ROS_Voltage_Meter : public QQuickPaintedItem {
    // make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Voltage_Meter(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);

        // getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();

    private:
        void receive_volt_val(const std_msgs::Float32::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Subscriber volt_sub;
        QString topic_value;
        bool ros_ready;

        int data; // the voltage
};

#endif // ROS_VOLTAGE_METER_H
