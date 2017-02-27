/**
* Date Started: 25/02/2017
* Original Author: Harry J.E Day
* Editors:
* ROS Node Name: joystick_receiver
* ROS Package: owr_arduino_joystick
* Purpose: Node that pulls data from an arduino and transfers it to the control systems
* Based on Bluetongue.cpp
* Released under the MIT License. Copyright BLUEsat UNSW 2017
*/

#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "owr_arduino_joystick/joystick_receiver_node.hpp"
#include "owr_arduino_joystick/communication_structs.hpp"

#define DODGY_USB_CONNECTION 100

int main(int argc, char ** argv) {
    //init ros
    ros::init(argc, argv, "owr_position_node");
    ros::NodeHandle nh;
    Joystick_Receiver_Node p(nh);
    p.spin();

    return EXIT_SUCCESS;
}

Joystick_Receiver_Node::Joystick_Receiver_Node(ros::NodeHandle nh) {
    twist_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1, false);
    arm_base_rotation = nh.advertise<std_msgs::Float32>("/arm_base_rotate_controller/command", 1, false);
    arm_upper_pwm = nh.advertise<std_msgs::Float32>("/upper_arm_act_controller/command", 1, false);
    arm_lower_pwm = nh.advertise<std_msgs::Float32>("/lower_arm_act_controller/command", 1, false);
    claw_grip = nh.advertise<std_msgs::Float32>("/claw_grip_controller/command", 1, false);
    claw_rotate = nh.advertise<std_msgs::Float32>("/claw_rotate_controller/command", 1, false);

}


void Joystick_Receiver_Node::spin() {
    bool ok;
    Frm_Arduino frm_arduino;
    To_Arduino to_arduino;
    while(ros::ok()) {
        while(!open_arduino()) {}
        ROS_INFO("Open Succesfully");
        while(ros::ok()) {
            ok = comm(&to_arduino, sizeof(To_Arduino), &frm_arduino, sizeof(Frm_Arduino));
            if(ok) {
                geometry_msgs::Twist twst;
                twst.linear.x = frm_arduino.drive_direction.x;
                twst.linear.y = frm_arduino.drive_direction.y;
                twist_pub.publish(twst);

                std_msgs::Float32 msg;
                msg.data = frm_arduino.arm_base_rotation;
                arm_base_rotation.publish(msg);

                msg.data = frm_arduino.arm_upper_pwm;
                arm_upper_pwm.publish(msg);

                msg.data = frm_arduino.arm_lower_pwm;
                arm_lower_pwm.publish(msg);

                msg.data = frm_arduino.claw_grip_position;
                claw_grip.publish(msg);

                msg.data = frm_arduino.claw_rotation_speed;
                claw_rotate.publish(msg);
                ROS_INFO("Packet Received");
            } else {
                ROS_ERROR("Connection failed");
                break;
            }
            ros::spinOnce();
        }
    }
}


bool Joystick_Receiver_Node::open_arduino() {
    // TODO: write something to find arduinos
    port_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK);

    if(port_fd == -1) {
        ROS_ERROR("Error in open uart port");
        return false;
    } else {
        ROS_DEBUG("Open uart port");
    }
    // Set up stuff for select so we can timeout on reads
    FD_ZERO(&uart_set); /* clear the set */
    FD_SET(port_fd, &uart_set); /* add our file descriptor to the set */
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    // Set parameters
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    // Error Handling
    if (tcgetattr(port_fd, &tty) != 0) {
        ROS_ERROR("Error %d from tcgetattr: %s", errno, strerror(errno));
        close(port_fd);
        return false;
    }
    ROS_DEBUG("Setting up uart");

    // Set Baud Rate
    cfsetospeed(&tty, (speed_t)B19200);
    cfsetispeed(&tty, (speed_t)B19200);

    // Setting other Port Stuff
    tty.c_cflag &= ~PARENB; // Make 8n1
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    tty.c_cflag &= ~CRTSCTS; // no flow control
    tty.c_cc[VMIN] = 1; // read doesn't block
    tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout
    tty.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines
    ROS_DEBUG("About to make raw");

    // Make raw
    cfmakeraw(&tty);

    // Flush Port, then applies attributes
    tcflush(port_fd, TCIFLUSH);
    if (tcsetattr(port_fd, TCSANOW, &tty) != 0) {
        ROS_ERROR("Error %d from tcsetattr: %s" ,errno, strerror(errno));
        close(port_fd);
        return false;
    }

    return true;
}

bool Joystick_Receiver_Node::comm(void *message, int message_len, void *resp, int resp_len) {
    ROS_DEBUG("Writing message: ");
    for (int i = 0; i < message_len; i++) {
        ROS_DEBUG("%d: %02x\n", i, *((char *) message + i));
    }
    int written = 0;
    timeout.tv_sec = 0;
    timeout.tv_usec = 400000;
    int empty_writes = 0;
    do {
        int write_amount = write(port_fd, (int8_t*)message + written, message_len - written);
        if (write_amount == -1) {
            ROS_ERROR("USB write error");
            return false;
        }
        written += write_amount;
        if (write_amount == 0) ++empty_writes;
        if (empty_writes > DODGY_USB_CONNECTION) {
            ROS_ERROR("Dodgy usb connection detected");
            return false;
        }
    } while (written < message_len);

    ROS_DEBUG("Written packet, expecting to read %d", resp_len);
    tcflush(port_fd, TCIOFLUSH);
    int empty_reads = 0;
    int readCount = 0;
    bool first_read = false;
    do {
        int rv = select(port_fd + 1, &uart_set, NULL, NULL, &timeout);
        if(rv == -1) {
            ROS_ERROR("select"); /* an error accured */
            return false;
        } else if(rv == 0) {
            ROS_ERROR("timeout"); /* a timeout occured */
            return false; // This might not require a full reset...
        } else {
            int read_amount = read(port_fd, (int8_t*)resp + readCount, resp_len - readCount);
            readCount += read_amount;
            if (read_amount == 0) ++empty_reads;
            if(!first_read) {
                if (read_amount > 1 && *(uint16_t *) resp == 0xBEEF) {
                    first_read = true;
                } else {
                    readCount = 0;
                    continue;
                }
            }
            if (empty_reads > DODGY_USB_CONNECTION) {
                ROS_ERROR("Dodgy usb connection detected");
                return false;
            }
        }
        ROS_DEBUG("reading... %d", readCount);
    } while (readCount < resp_len);
    ROS_DEBUG("Read packet");
    return true;
}
