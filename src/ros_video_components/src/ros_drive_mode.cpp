/*
 * Date Started: 13/08/18
 * Original Author: Harry J.E Day
 * Editors:
 * Purpose: Joystick listener used to receive joystick messages
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2018
 */

#include "ros_video_components/ros_drive_mode.hpp"

void Ros_Drive_Mode::set_topic(const QString & new_value) {
    ROS_INFO("new value %s", new_value.toStdString().c_str());
    if(topic_value != new_value) {
        topic_value = new_value;
        if(!topic_value.isEmpty()) {
            if(ros_ready) {
                ROS_INFO("new value %s", new_value.toStdString().c_str());
                mode_sub.shutdown();
                mode_sub = nh->subscribe(
                      topic_value.toStdString(),
                      1,
                      &Ros_Drive_Mode::mode_callback,
                      this
                );
            }
        } else {
            mode_sub.shutdown();
        }
        emit topic_changed();
    }
}

QString Ros_Drive_Mode::get_topic() const {
    return topic_value;
}

QString Ros_Drive_Mode::get_mode() const {
    return mode_value;
}

void Ros_Drive_Mode::setup(ros::NodeHandle * nh) {
    this->nh = nh;
    if(!topic_value.isEmpty()) {
        ROS_INFO("Looking for joysticks at %s", topic_value.toStdString().c_str());
        mode_sub = nh->subscribe(
              topic_value.toStdString(),
              1,
              &Ros_Drive_Mode::mode_callback,
              this
        );
    }


    ros_ready = true;

}

void Ros_Drive_Mode::mode_callback(const std_msgs::Int16::ConstPtr & msg) {

    switch(msg->data) {
        case CRAB:
            mode_value = QString("CRAB ");
            break;
        case FOUR:
            mode_value = QString("FOUR ");
            break;
        case SWERVE:
            mode_value = QString("SERVE");
            break;
    }
    emit mode_changed();
}
