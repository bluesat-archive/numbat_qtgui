/*
 * Date Started: 13/08/18
 * Original Author: Harry J.E Day
 * Editors:
 * Purpose: Joystick listener used to receive joystick messages
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2018
 */

#include "ros_video_components/ros_joystick_listener.hpp"

void Ros_Joystick_Listener::set_topic(const QString & new_value) {
    ROS_INFO("new value %s", new_value.toStdString().c_str());
    if(topic_value != new_value) {
        topic_value = new_value;
        if(!topic_value.isEmpty()) {
            if(ros_ready) {
                ROS_INFO("new value %s", new_value.toStdString().c_str());
                joy_sub.shutdown();
                joy_sub = nh->subscribe(
                      topic_value.toStdString(),
                      1,
                      &Ros_Joystick_Listener::joystick_callback,
                      this
                );
            }
        } else {
            joy_sub.shutdown();
        }
        emit topic_changed();
    }
}

QString Ros_Joystick_Listener::get_topic() const {
    return topic_value;
}


void Ros_Joystick_Listener::setup(ros::NodeHandle * nh) {
    this->nh = nh;
    if(!topic_value.isEmpty()) {
        ROS_INFO("Looking for joysticks at %s", topic_value.toStdString().c_str());
        joy_sub = nh->subscribe(
              topic_value.toStdString(),
              1,
              &Ros_Joystick_Listener::joystick_callback,
              this
        );
    }


    ros_ready = true;

}
void Ros_Joystick_Listener::joystick_callback(const sensor_msgs::Joy::ConstPtr & msg) {

    if(current_state.buttons.size() != msg->buttons.size()) {
        current_state.buttons.resize(msg->buttons.size());
    }
    // go through each button and signal any changes
    for(int i = 0; i < msg->buttons.size(); ++i) {
        if(msg->buttons[i] != current_state.buttons[i]) {
            current_state.buttons[i] = msg->buttons[i];
            if(msg->buttons[i]) {
                emit button_down(i);
            } else {
                emit button_up(i);
            }
        }
    }
}
