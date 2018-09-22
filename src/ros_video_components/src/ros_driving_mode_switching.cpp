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

#include "ros_video_components/ros_driving_mode_switching.hpp"

ROS_Driving_Mode_Switching::ROS_Driving_Mode_Switching(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/rover/driving_mode_switching/"),
    ros_ready(false),
    a(0),
    data(50) {
}

void ROS_Driving_Mode_Switching::setup(ros::NodeHandle * nh) {

    drive_mode_pub = nh->advertise<std_msgs::Float32>(
        "/rover/driving_mode_switching/", //Post to this topic
         1,
         true
    );
    ros_ready = true;
    //ROS_INFO("Setup of driving mode switching component complete");
}

void ROS_Driving_Mode_Switching::paint(QPainter *painter){
    //do nothing because gui is done in main_window.qml
}

void  ROS_Driving_Mode_Switching::sendmessage() {
   std_msgs::Float32 msg;
    msg.data = 1000;
    drive_mode_pub.publish(msg);
    //when the key 'A/S/D'pressed, a should add 1
    a++;
    ROS_INFO("value is %d",a);
    // ros::spinOnce();
}


QString ROS_Driving_Mode_Switching::get_topic() const {
    return topic_value;
}

void ROS_Driving_Mode_Switching::set_topic(const QString & new_value) {
    ROS_INFO("set_topic");
    if(topic_value != new_value) {
        topic_value = new_value;
        if(ros_ready) {
            drive_mode_pub.shutdown();
            drive_mode_pub = nh->advertise<std_msgs::Float32>(
               "/rover/driving_mode_switching/",
                1,
                true
            );
        }
        emit topic_changed();
    }
}

void ROS_Driving_Mode_Switching::receive_drive_mode_command(const std_msgs::Float32::ConstPtr & msg){
    data = msg->data;
    ROS_INFO("Received signal message");
    update();
}
