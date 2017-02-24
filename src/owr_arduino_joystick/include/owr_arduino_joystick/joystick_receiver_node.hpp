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

#include <std_msgs/float64.h>
#include <geometry_msgs/twist.hpp>

class Joystick_Receiver_Node {
    public:
        Joystick_Receiver_Node(NodeHandle nh);
    private:
        ros::publisher twistPub;
};


#endif //PROJECT_JOYSTICK_RECEIVER_NODE_HPP
