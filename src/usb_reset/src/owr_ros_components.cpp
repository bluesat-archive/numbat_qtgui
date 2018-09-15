#include "usb_reset/owr_ros_components.hpp"
#include "usb_reset/usb_reset.hpp"

void Owr_Ros_Components::registerTypes(const char *uri) {
    qmlRegisterType<ROS_Usb_Reset>("bluesat.owr", 1, 0, "usb_reset");
}
