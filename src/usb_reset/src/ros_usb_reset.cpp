#include "usb_reset/ros_usb_reset.hpp"
#include <iostream>

ROS_Usb_Reset::ROS_Usb_Reset(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value(),
    ros_ready(false),
    devices("no devices") {

}

void ROS_Usb_Reset::setup(ros::NodeHandle * nh) {

    //TODO: make these parameters of the component
      usb_sub = nh->subscribe(
            topic_value.toStdString(),
            1,
            &ROS_Usb_Reset::receive_msg,
            this
      );

    ros_ready = true;
    ROS_INFO("Setup of usb component complete");
}

void ROS_Usb_Reset::receive_msg(const std_msgs::String::ConstPtr &msg) {
    //figure this out
    devices = msg->data;
    ROS_INFO("Received usb message");
    update();
}

void ROS_Usb_Reset::paint(QPainter * painter) {
  QLinearGradient linearGradient(0, 0, 100, 100);
  linearGradient.setColorAt(0.2, Qt::yellow);
  painter->setBrush(linearGradient);
  painter->drawRect(10,10,20,20);
}

void ROS_Usb_Reset::set_topic(const QString & new_value) {
    ROS_INFO("new value %s", new_value.toStdString().c_str());
    if(topic_value != new_value) {
        topic_value = new_value;
        if(!topic_value.isEmpty()) {
            if(ros_ready) {
                ROS_INFO("new value %s", new_value.toStdString().c_str());
                usb_sub.shutdown();
                usb_sub = nh->subscribe(
                      topic_value.toStdString(),
                      1,
                      &ROS_Usb_Reset::receive_msg,
                      this
                );
            }
        } else {
            usb_sub.shutdown();
        }
        emit topic_changed();
    }
}

QString ROS_Usb_Reset::get_topic() const {
    return topic_value;
}
