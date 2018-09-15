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
       /**
        * Constructor for the ROS_Drive_Mode class, initialises default variables
        * @param parent the parent widget
        */
       Ros_Drive_Mode(QQuickItem * parent = 0) :
       topic_value(),
       mode_value("---- "),
       ros_ready(false),
       QQuickItem(parent) {}

        //getters and setters

        /**
         * Used to handle the topic being set in qml.
         * Updates the subscriber
         * @param new_value the new value for the topic.
         */
        void set_topic(const QString &new_value);
        /**
         * Used to retrieve the topic from QML
         * @return the value of the topic string
         */
        QString get_topic() const;
        /**
         * Used to retrieve the string representing the driving mode
         * @return the string of the mode
         */
        QString get_mode() const;
        /**
         * Called to set the node handle.
         * Initalises all of the ros functionality.
         * @param nh the node handle
         */
        void setup(ros::NodeHandle * nh);

    signals:
        /**
         * Emitted when the topic is channged
         */
        void topic_changed();
        /**
         * Emitted when we receive a new mode callback
         */
        void mode_changed();

    private:
        /**
         * Ros callback for the mode being changed
         * @param msg the mode message
         */
        void mode_callback(const std_msgs::Int16::ConstPtr & msg);

        QString topic_value;
        bool ros_ready;
        ros::Subscriber mode_sub;
        ros::NodeHandle * nh;
        QString mode_value;

};
#endif // ROS_DRIVE_MODE_H
