#include "ros_video_components/owr_ros_components.hpp"
#include "ros_video_components/ros_video_component.hpp"
#include "ros_video_components/rover_cmd_state.hpp"

#include <QQmlEngine>

void OWR_ROS_Components::registerTypes(const char *uri) {
    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "ROSVideoComponent");
    qmlRegisterSingletonType<Rover_Cmd_State>("bluesat.owr.singleton", 1, 0, "RoverCmdState", &Rover_Cmd_State::qml_instance);
}
