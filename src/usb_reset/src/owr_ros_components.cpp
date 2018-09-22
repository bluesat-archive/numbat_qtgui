/*
 * Date Started: 25/07/16
 * Original Author: Harry J.E Day
 * Editors:
 * Purpose: C++ code representation of the QML package
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2017
 */
#include "usb_reset/owr_ros_components.hpp"
#include "usb_reset/ros_usb_reset.hpp"

void OWR_ROS_Components::registerTypes(const char *uri) {
    qmlRegisterType<ROS_Usb_Reset>("bluesat.owr", 1, 0, "ROSUsbReset");
}
