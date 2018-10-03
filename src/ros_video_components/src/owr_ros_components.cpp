/*
 * Date Started: 25/07/16
 * Original Author: Harry J.E Day
 * Editors:
 * Purpose: C++ code representation of the QML package
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2017
 */
#include "ros_video_components/owr_ros_components.hpp"
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_wheel_visualize.hpp"
#include "ros_video_components/ros_signal_strength.hpp"
#include "ros_video_components/ros_voltage_meter.hpp"
#include "ros_video_components/ros_camera_switching.hpp"
#include "ros_video_components/ros_timer.hpp"
#include "ros_video_components/ros_joystick_listener.hpp"
#include "ros_video_components/ros_drive_mode.hpp"

void OWR_ROS_Components::registerTypes(const char *uri) {
    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");
    qmlRegisterType<ROS_Voltage_Meter>("bluesat.owr", 1, 0, "ROSVoltageMeter");
    qmlRegisterType<ROS_Camera_Switching>("bluesat.owr", 1, 0, "ROSCameraSwitching");
    qmlRegisterType<ROSTimer>("bluesat.owr", 1, 0, "ROSTimer");
    qmlRegisterType<Ros_Joystick_Listener>("bluesat.owr", 1, 0, "ROSJoystickListener");
    qmlRegisterType<ROS_Wheel_Visualize>("bluesat.owr", 1, 0, "ROSWheelVisualize");
    qmlRegisterType<Ros_Drive_Mode>("bluesat.owr", 1, 0, "ROSDriveMode");

}
