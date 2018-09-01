#include "ros_video_components/owr_ros_components.hpp"
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/ros_signal_strength.hpp"

//add the new include directory
#include "ros_video_components/ros_driving_mode_switching.hpp"

void OWR_ROS_Components::registerTypes(const char *uri) {
    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterType<ROS_Signal_Strength>("bluesat.owr", 1, 0, "ROSSignalStrength");

    //new Register Type
    qmlRegisterType<ROS_Driving_Mode_Switching>("bluesat.owr", 1, 0, "ROSDrivingModeSwitching");
}
