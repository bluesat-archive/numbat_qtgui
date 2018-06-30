#include "ros_video_components/owr_ros_components.hpp"
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_signal_strength.hpp"
#include "ros_video_components/ros_battery_indicator.hpp"

void OWR_ROS_Components::registerTypes(const char *uri) {
    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");
    qmlRegisterType<ROS_Battery_Indicator>("bluesat.owr", 1, 0, "ROSBatteryIndicator"); //added
}
