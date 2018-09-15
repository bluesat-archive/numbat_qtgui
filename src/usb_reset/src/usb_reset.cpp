#include "usb_reset/usb_reset.hpp"

ROS_Usb_Reset::ROS_Usb_Reset(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/rover/usb"),
    ros_ready(false),
    devices("No devices") {
}

void ROS_Usb_Reset::setup(ros::NodeHandle * nh) {

    signal_sub = nh->subscribe(
        "/rover/usb", //TODO
        1,
        &ROS_Usb_Reset::receive_signal,
        this
    );
    ros_ready = true;
}

void ROS_Usb_Reset::paint(QPainter * painter) {
  QString dev = QString::fromStdString(devices);
  painter->drawText(10, 10, dev);
  //painter->drawRect(10, 10, 50, 50);

}

void ROS_Usb_Reset::set_topic(const QString & new_value) {
    ROS_INFO("set_topic");
    if(topic_value != new_value) {
        topic_value = new_value;
        if(ros_ready) {
            signal_sub.shutdown();
            signal_sub = nh->subscribe(
                topic_value.toStdString(), //TODO
                1,
                &ROS_Usb_Reset::receive_signal,
                this
            );
        }
        emit topic_changed();
    }
}

QString ROS_Usb_Reset::get_topic() const {
    return topic_value;
}

void ROS_Usb_Reset::
      receive_signal(const std_msgs::String::ConstPtr & msg) {
    devices = msg->data;
    ROS_INFO("Received usb message");
    update();
}
