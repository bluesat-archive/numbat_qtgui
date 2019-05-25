#include "usb_reset/usb_reset.hpp"

int num = 0;

ROS_Usb_Reset::ROS_Usb_Reset(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value(),
    ros_ready(false),
    num(0),
    devices() {

}

void ROS_Usb_Reset::setup(ros::NodeHandle * nh, QQmlContext *ctxt) {
      usb_sub = nh->subscribe(
            "rover/usb",
            1,
            &ROS_Usb_Reset::receive_msg,
            this
      );
      usb_pub = nh->advertise<std_msgs::Int16>(
                    "rover/usb/reset",
                    1,
                    false
            );

    ros_ready = true;
    curr_ctxt = ctxt;
    ROS_INFO("Setup of usb component complete");
}

void ROS_Usb_Reset::receive_msg(const owr_messages::devices::ConstPtr & msg) {
    int i = 0;
    for(; i < msg->devices.size(); i++) {
        devices[i] = msg->devices[i];
    }
    num = i;
    update();
}

void ROS_Usb_Reset::paint(QPainter * painter) {QLinearGradient linearGradient(0, 0, 100, 100);
  linearGradient.setColorAt(0.2, Qt::yellow);
  painter->setBrush(linearGradient);
  painter->setPen(Qt::green);
  int i = 0;
  //create the neccessary number of buttons
  curr_ctxt->setContextProperty("usbDevices", (num - 1));
  for (; i < num - 1; i++) {
      //write the name of the usb device
      painter->drawText(75,(i*35) + 15, QString::fromStdString(devices[i]));
  }

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

void ROS_Usb_Reset::publish(int num) {
    std_msgs::Int16 a;
    a.data = num;
    usb_pub.publish(a);
}

int ROS_Usb_Reset::num_devices() {
  return num;
}
