#include "ros_video_components/rover_cmd_state.hpp"

Rover_Cmd_State::Rover_Cmd_State(QObject *parent) :
    QObject(parent),
    nh(NULL),
    drive_x(0.0),
    drive_y(0.0),
    arm_lower(0.0),
    arm_upper(0.0),
    arm_rotation(0.0),
    claw_rot_speed(0.0),
    claw_grip(0.0) {



}

void Rover_Cmd_State::setup(ros::NodeHandle *nh) {
    this->nh = nh;


    ros::TransportHints transportHints = ros::TransportHints().tcp();
    cmd_vel_sub = nh->subscribe<geometry_msgs::Twist>("/cmd_vel", 1, &Rover_Cmd_State::cmd_vel_callback, this, transportHints);
    arm_upper_sub = nh->subscribe<std_msgs::Float64>("/upper_arm_act_controller/command", 1, &Rover_Cmd_State::arm_upper_callback, this, transportHints);
    arm_lower_sub = nh->subscribe<std_msgs::Float64>("/lower_arm_act_controller/command", 1, &Rover_Cmd_State::arm_lower_callback, this, transportHints);
    arm_rotation_sub = nh->subscribe<std_msgs::Float64>("/arm_base_rotate_controller/command", 1, &Rover_Cmd_State::arm_rotation_callback, this, transportHints);
    claw_grip_sub = nh->subscribe<std_msgs::Float64>("/claw_grip_controller/command", 1, &Rover_Cmd_State::claw_grip_callback, this, transportHints);
    claw_rot_speed_sub = nh->subscribe<std_msgs::Float64>("/claw_rotate_controller/command", 1, &Rover_Cmd_State::claw_rot_speed_callback, this, transportHints);
}

void Rover_Cmd_State::cmd_vel_callback(const geometry_msgs::Twist::ConstPtr &msg) {

    drive_x = msg->linear.x;
    drive_y = msg->linear.y;
    emit drive_x_changed();
    emit drive_y_changed();
    emit cmd_vel_changed();
}

void Rover_Cmd_State::arm_lower_callback(const std_msgs::Float64::ConstPtr &msg) {
    arm_lower = msg->data;
    emit arm_lower_changed();
}
void Rover_Cmd_State::arm_upper_callback(const std_msgs::Float64::ConstPtr &msg) {
    arm_upper = msg->data;
    emit arm_upper_changed();
}
void Rover_Cmd_State::arm_rotation_callback(const std_msgs::Float64::ConstPtr &msg) {
    arm_rotation = msg->data;
    emit arm_rotation_changed();
}
void Rover_Cmd_State::claw_grip_callback(const std_msgs::Float64::ConstPtr &msg) {
    claw_grip = msg->data;
    emit claw_grip_changed();
}
void Rover_Cmd_State::claw_rot_speed_callback(const std_msgs::Float64::ConstPtr &msg) {
    claw_rot_speed = msg->data;
    emit claw_rot_speed_changed();
}

float Rover_Cmd_State::get_drive_x() const {
    return drive_x;
}

float Rover_Cmd_State::get_drive_y() const {
    return drive_y;
}
float Rover_Cmd_State::get_arm_lower() const {
    return arm_lower;
}
float Rover_Cmd_State::get_arm_upper() const {
    return arm_upper;
}
float Rover_Cmd_State::get_arm_rotation() const {
    return arm_rotation;
}
float Rover_Cmd_State::get_claw_grip() const {
    return claw_grip;
}
float Rover_Cmd_State::get_claw_rot_speed() const {
    return claw_rot_speed;
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
