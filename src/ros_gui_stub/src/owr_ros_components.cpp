#include "ros_gui_stub/owr_ros_components.hpp"
// TODO: change this
#include "ros_gui_stub/ros_gui_stub.hpp"


void OWR_ROS_Components::registerTypes(const char *uri) {
    // TODO: add your components here
    qmlRegisterType<ROS_Video_Component>("bluesat.owr", 1, 0, "RosGuiStub");
}
