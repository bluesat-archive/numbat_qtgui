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

ROS_Voltage_Meter::ROS_Voltage_Meter(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/rover/volt"),
    ros_ready(false),
    data(50) {}

void ROS_Voltage_Meter::setup(ros::NodeHandle * nh) {
    volt_sub = nh->subscribe(
        "/rover/volt",
        1,
        &ROS_Voltage_Meter::receive_volt_val,
        this);
    ros_ready = true;
}

void ROS_Voltage_Meter::paint(QPainter * painter) {
    // TODO(sajidanower23)
}

void ROS_Voltage_Meter::set_topic(const QString & new_value) {
    // ROS_INFO("set_topic");
    if (topic_value != new_value) {
        topic_value = new_value;
        if (ros_ready) {
            volt_sub.shutdown();
            volt_sub = nh->subscribe(
                topic_value.toStdString(),
                1,
                &ROS_Voltage_Meter::receive_volt_val,
                this);
        }
        emit topic_changed();
    }
}

QString ROS_Voltage_Meter::get_topic() const {
    return topic_value;
}

void ROS_Voltage_Meter :: receive_volt_val(const std_msgs::Float32::ConstPtr & msg) {
    data = msg->data;
    ROS_INFO("Received voltage update");
    update();
}
