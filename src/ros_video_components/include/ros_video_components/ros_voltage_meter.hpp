/*
 * Date Started: 8/09/18
 * Original Author: Sajid Ibne Anower
 * Editors:
 * Purpose: Widget to display voltage of the batteries
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2018
 */
#ifndef ROS_VOLTAGE_METER_H
#define ROS_VOLTAGE_METER_H

// QT
#include <QObject>
#include <QQuickItem>

// ROS
#include <ros/ros.h>
#include <std_msgs/Float32.h>

class ROS_Voltage_Meter : public QQuickItem {
    // make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)
    Q_PROPERTY(float volt_value READ get_volt NOTIFY volt_update)

    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Voltage_Meter(QQuickItem * parent = 0);

        void setup(ros::NodeHandle * nh);

        // getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;
        float get_volt() const;

    signals:
        void topic_changed();
        void volt_update();

    private:
        void receive_volt_val(const std_msgs::Float32::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Subscriber volt_sub;
        QString topic_value;
        bool ros_ready;
        ros::Subscriber volt_sub;
        ros::NodeHandle * nh;
        float volt_value;
};

#endif // ROS_VOLTAGE_METER_H
