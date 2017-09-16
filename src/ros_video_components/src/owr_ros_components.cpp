#include "ros_video_components/owr_ros_components.hpp"
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_wheel_visualize.hpp"
#include "ros_video_components/ros_signal_strength.hpp"

void OWR_ROS_Components::registerTypes(const char *uri) {
    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");
    qmlRegisterType<ROS_Wheel_Visualize>("bluesat.owr", 1, 0, "ROSWheelVisualize");
}
