#include "usb_reset/ros_usb_reset.hpp"

int num = 0;

ROS_Usb_Reset::ROS_Usb_Reset(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value(),
    ros_ready(false),
    devices("no devices") {

}

void ROS_Usb_Reset::setup(ros::NodeHandle * nh, QQmlContext *ctxt) {

    //TODO: make these parameters of the component
      usb_sub = nh->subscribe(
            topic_value.toStdString(),
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

void ROS_Usb_Reset::receive_msg(const std_msgs::String::ConstPtr &msg) {
    devices = msg->data;
    //ROS_INFO("Received usb message");
    update();
}

void ROS_Usb_Reset::paint(QPainter * painter) {
  QLinearGradient linearGradient(0, 0, 100, 100);
  linearGradient.setColorAt(0.2, Qt::yellow);
  painter->setBrush(linearGradient);
  painter->setPen(Qt::green);
  int i = 0;
  QString dev = QString::fromStdString(devices);
  QStringList list = dev.split("#/#/");
  curr_ctxt->setContextProperty("myModel", (list.size() - 1));
  for (; i < list.size(); i++) {
      painter->drawText(75,(i*35) + 15, list[i]);
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
