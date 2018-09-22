/*
 * Date Started: 28/07/18
 * @author: Linchuan YANG
 * @editors:
 * ROS Node Name: not applicable
 * ROS Package: owr_qtgui
 * @description: This code generates a publisher called signal_pub, which will make a variable called a increase by 1
 * when keyA/S/D are pressed and print it out
 * @copyright: This code is released under the MIT License. Copyright BLUEsat UNSW, 2018
 */

#ifndef ROS_DRIVING_MODE_SWITCHNG_HPP
#define ROS_DRIVING_MODE_SWITCHNG_HPP

//QT
#include <QQuickPaintedItem>
#include <QPainter>
#include <QQmlApplicationEngine>

//ROS
#include <ros/ros.h>
#include <std_msgs/Float32.h>

class ROS_Driving_Mode_Switching : public QQuickPaintedItem {
    //make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Driving_Mode_Switching(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        Q_INVOKABLE  void sendmessage();
        void setup(ros::NodeHandle * nh);

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();

    private:
        void receive_drive_mode_command(const std_msgs::Float32::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Publisher drive_mode_pub;
        QString topic_value;
        bool ros_ready;
        int a;
        int data; //the drive mode switching data
};

#endif // ROS_DRIVING_MODE_SWITCHNG_HPP
