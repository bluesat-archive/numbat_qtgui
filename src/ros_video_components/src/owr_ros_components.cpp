#include "ros_video_components/owr_ros_components.hpp"
#include "ros_video_components/ros_video_component.hpp"


void OWR_ROS_Components::registerTypes(const char *uri) {
    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
}
