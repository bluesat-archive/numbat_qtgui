/**
 * Date Started: 01/09/18
 * Original Author: Harry J.E Day
 * Editors:
 * Purpose: Shows the driving mode
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2018
 */
#ifndef ROS_DRIVE_MODE_H
#define ROS_DRIVE_MODE_H


#include <QObject>
#include <QQuickItem>

#include <std_msgs/Int16.h>
#include <ros/ros.h>

const short CRAB = 0;
const short FOUR = 1;
const short SWERVE = 2;

class Ros_Drive_Mode : public QQuickItem {
    //make this a Qt Widget
    Q_OBJECT

    /**
     * defines a qml value for the topic to subscribe to
     */
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)
    Q_PROPERTY(QString mode READ get_mode NOTIFY mode_changed)


   public:
       Ros_Drive_Mode(QQuickItem * parent = 0) :
       topic_value(),
       mode_value("---- "),
       ros_ready(false),
       QQuickItem(parent) {}

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;
        QString get_mode() const;
        void setup(ros::NodeHandle * nh);

    signals:
        void topic_changed();
        void mode_changed();

    private:
        void mode_callback(const std_msgs::Int16::ConstPtr & msg);
        QString topic_value;
        bool ros_ready;
        ros::Subscriber mode_sub;
        ros::NodeHandle * nh;
        QString mode_value;

};
#endif // ROS_DRIVE_MODE_H
