/*
 * Date Started: 8/09/18
 * Original Author: Sajid Ibne Anower
 * Editors:
 * Purpose: Widget to display voltage of the batteries
 * This code is released under the MIT License. Copyright BLUEsat UNSW 2018
 * Trivia: This code was written on the plane from Sydney to Warsaw,
 * on the way to participating in ERC2018
 */
#include "ros_video_components/ros_voltage_meter.hpp"

void ROS_Voltage_Meter::setup(ros::NodeHandle * nh) {
    volt_sub = nh->subscribe(
        "/rover/volt",
        1,
        &ROS_Voltage_Meter::receive_volt_callback,
        this);
    ros_ready = true;
}

void ROS_Voltage_Meter::set_topic(const QString & new_value) {
    if (topic_value != new_value) {
        topic_value = new_value;
        if (ros_ready) {
            volt_sub.shutdown();
            volt_sub = nh->subscribe(
                topic_value.toStdString(),
                1,
                &ROS_Voltage_Meter::receive_volt_callback,
                this);
        }
        emit topic_changed();
    }
}

QString ROS_Voltage_Meter::get_topic() const {
    return topic_value;
}

double ROS_Voltage_Meter::get_volt() const {
    return volt_value;
}

void ROS_Voltage_Meter :: receive_volt_callback(const std_msgs::Float32::ConstPtr & msg) {
    volt_value = msg->data;
    emit volt_update();
}
