/**
* Date Started: 25/02/2017
* Original Author: Harry J.E Day
* Editors:
* ROS Node Name: joystick_receiver
* ROS Package: owr_arduino_joystick
* Purpose: Node that pulls data from an arduino and transfers it to the control systems
*/
#ifndef PROJECT_JOYSTICK_RECEIVER_NODE_HPP
#define PROJECT_JOYSTICK_RECEIVER_NODE_HPP

#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>

class Joystick_Receiver_Node {
    public:
        Joystick_Receiver_Node(ros::NodeHandle nh);
        void spin();

    private:
        bool open_arduino();
        fd_set uart_set;
        struct timeval timeout;
        int port_fd;

        ros::Publisher twist_pub;
        ros::Publisher claw_rotate;
        ros::Publisher claw_grip;
        ros::Publisher arm_base_rotation;
        ros::Publisher arm_lower_pwm;
        ros::Publisher arm_upper_pwm;
        bool comm(void *message, int message_len, void *resp, int resp_len);

};


#endif //PROJECT_JOYSTICK_RECEIVER_NODE_HPP
