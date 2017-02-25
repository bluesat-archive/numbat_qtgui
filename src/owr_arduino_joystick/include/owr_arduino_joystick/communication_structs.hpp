/**
* Date Started: 25/02/2017
* Original Author: Harry J.E Day
* Editors:
* ROS Package: owr_arduino_joystick
* Purpose: Used to store the structs for communication with the arduino
* Released under the MIT License, Copyright 2017 BLUEsat UNSW
*/
#ifndef COMMUNICATION_STRUCTS_HPP
#define COMMUNICATION_STRUCTS_HPP

typedef struct _frm_arduino {

    const int magic1 = 0xBEEF;

    // the drive direction command
    struct _vector {
        double x;
        double y;
    } drive_direction;

    /* Arm Related Functions */

    // the rotation of the arm (rads)
    double arm_base_rotation;
    // the extension of the upper and lower parts of the arm (m)
    double arm_lower_extension;
    double arm_upper_extension;

    /* Claw Related Functions */

    // the rotation speed of the claw (rads/s)
    double claw_rotation_speed;
    // the grip postion of the claw (pwm)
    double claw_grip_position;

    const int magic2 = 0xF00D;

} Frm_Arduino;

#endif // COMMUNICATION_STRUCTS_HPP
