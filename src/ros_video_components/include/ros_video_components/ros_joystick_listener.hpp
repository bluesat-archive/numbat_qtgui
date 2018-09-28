/*
 * Date Started: 13/08/18
 * Original Author: Harry J.E Day
 * Editors:
 * Purpose: Joystick listener used to receive joystick messages
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2018
 */
#ifndef ROS_JOYSTICK_LISTENER_H
#define ROS_JOYSTICK_LISTENER_H


#include <QObject>
#include <QQuickItem>

#include <sensor_msgs/Joy.h>
#include <ros/ros.h>


class Ros_Joystick_Listener : public QQuickItem {
    //make this a Qt Widget
    Q_OBJECT

    /**
     * defines a qml value for the topic to subscribe to
     */
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)


   public:
       Ros_Joystick_Listener(QQuickItem * parent = 0) :
           topic_value(),
           ros_ready(false),
           QQuickItem(parent) {}

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;
        void setup(ros::NodeHandle * nh);

    signals:
        void topic_changed();
        void button_down(const qint32 & button);
        void button_up(const qint32 & button);

    private:
        void joystick_callback(const sensor_msgs::Joy::ConstPtr & msg);
        QString topic_value;
        bool ros_ready;
        ros::Subscriber joy_sub;
        ros::NodeHandle * nh;
        sensor_msgs::Joy current_state;


};
#endif // ROS_JOYSTICK_LISTENER_H
