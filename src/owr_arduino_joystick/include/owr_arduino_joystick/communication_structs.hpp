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

#include <inttypes.h>

typedef struct _frm_arduino {

    uint16_t magic1;

    // the drive direction command
    struct _vector {
        float x;
        float y;
    }  __attribute__((packed)) drive_direction;

    /* Arm Related Functions */

    // the rotation of the arm (rads)
    float arm_base_rotation;
    // the extension speed of the upper and lower parts of the arm
    // (pwm. 1500 is stop, 2000 is full outwards, 1000 is full backwards)
    float arm_lower_pwm;
    float arm_upper_pwm;

    /* Claw Related Functions */

    // the rotation speed of the claw (rads/s)
    float claw_rotation_speed;
    // the grip postion of the claw (pwm)
    float claw_grip_position;

    uint16_t magic2;

} __attribute__((packed)) Frm_Arduino;

typedef struct _to_arduino {
    uint16_t magic = 0xBEEF;
} __attribute__((packed)) To_Arduino;

#endif // COMMUNICATION_STRUCTS_HPP
