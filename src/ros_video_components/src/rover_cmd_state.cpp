#include "ros_video_components/rover_cmd_state.hpp"

Rover_Cmd_State::Rover_Cmd_State(QObject *parent) : QObject(parent), nh(NULL),  drive_x(0.0), drive_y(0.0){

}

void Rover_Cmd_State::setup(ros::NodeHandle *nh) {
    this->nh = nh;

    ros::TransportHints transportHints = ros::TransportHints().tcp();
    cmd_vel_sub = nh->subscribe<geometry_msgs::Twist>("/cmd_vel", 1, &Rover_Cmd_State::cmd_vel_callback, this, transportHints);
}

void Rover_Cmd_State::cmd_vel_callback(const geometry_msgs::Twist::ConstPtr &msg) {

    drive_x = msg->linear.x;
    drive_y = msg->linear.y;
    emit drive_x_changed();
    emit drive_y_changed();
    emit cmd_vel_changed();
}

float Rover_Cmd_State::get_drive_x() const {
    return drive_x;
}

float Rover_Cmd_State::get_drive_y() const {
    return drive_y;
}

QObject * Rover_Cmd_State::qml_instance(QQmlEngine *engine, QJSEngine *script_engine) {
    Q_UNUSED(engine);
    Q_UNUSED(script_engine);

    if(instance == NULL) {
        instance = new Rover_Cmd_State();
    }
    return instance;
}

// because C++ is retarded
Rover_Cmd_State * Rover_Cmd_State::instance = NULL;