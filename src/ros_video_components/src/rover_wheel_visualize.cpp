#include "ros_video_components/ros_wheel_visualize.hpp"

#define RECT_X 5
#define RECT_Y 100
#define RECT_WIDTH RECT_X*40
#define RECT_HEIGHT 150

ROS_Wheel_Visualize::ROS_Wheel_Visualize(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    //Should be /rover/Wheel or /rover/Wheel_Visualize? or whatever?
    topic_value("/rover/Wheel"),
    ros_ready(false),
    data(50) {
}

void ROS_Wheel_Visualize::setup(ros::NodeHandle * nh) {
    
    wheel_sub = nh->subscribe("/rover/Wheel", 1, &ROS_Wheel_Visualize::receive_message,this);
    ros_ready = true;
    ROS_INFO("Setup of wheel video component complete");
}



void ROS_Wheel_Visualize::paint(QPainter * painter) {
    
    	int numOfWheelBox = 4;
	int x = RECT_X;
	int y = RECT_Y;
	int width = RECT_WIDTH;
	int height = RECT_HEIGHT;
    	QPainter painter();//what parameter should in the pointer?
    	painter.setBrush(Qt::red);
	for(int i=0; i<numOfWheelBox;i++){
    		painter.drawEclipse():
		painter->drawRect(x, y, widthV - 1, heightV - 1); 
	}
    	this->addItem(item);

	QLinearGradient linearGradient(0, 0, 100, 100);
	//which part can I get data from topic to choose poistion of triangle?
   	//How to set combined graph?
	
}

void ROS_Wheel_Visualize::set_topic(const QString & new_value) {
	ROS_INFO("set_topic");
    if(topic_value != new_value) {
        topic_value = new_value;
        if(ros_ready) {
            wheel_sub.shutdown();
            wheel_sub = nh->subscribe(topic_value.toStdString(),1,&ROS_Wheel_Visualize::receive_message,this);
        }
        emit topic_changed();
    }
}

QString ROS_Wheel_Visualize::get_topic() const {
    return topic_value;
}

void ROS_Wheel_Visualize::receive_message(const std_msgs::Float32::ConstPtr & msg){
	data = msg->data;
	ROS_INFO("Received wheel message");
	update();
}


// #include "ros_video_components/rover_cmd_state.hpp"

// Rover_Cmd_State::Rover_Cmd_State(QObject *parent) :
//     QObject(parent),
//     nh(NULL),
//     drive_x(0.0),
//     drive_y(0.0),
//     arm_lower(0.0),
//     arm_upper(0.0),
//     arm_rotation(0.0),
//     claw_rot_speed(0.0),
//     claw_grip(0.0) {



// }

// void Rover_Cmd_State::setup(ros::NodeHandle *nh) {
//     this->nh = nh;


//     ros::TransportHints transportHints = ros::TransportHints().tcp();
//     cmd_vel_sub = nh->subscribe<geometry_msgs::Twist>("/cmd_vel", 1, &Rover_Cmd_State::cmd_vel_callback, this, transportHints);
//     arm_upper_sub = nh->subscribe<std_msgs::Float64>("/upper_arm_act_controller/command", 1, &Rover_Cmd_State::arm_upper_callback, this, transportHints);
//     arm_lower_sub = nh->subscribe<std_msgs::Float64>("/lower_arm_act_controller/command", 1, &Rover_Cmd_State::arm_lower_callback, this, transportHints);
//     arm_rotation_sub = nh->subscribe<std_msgs::Float64>("/arm_base_rotate_controller/command", 1, &Rover_Cmd_State::arm_rotation_callback, this, transportHints);
//     claw_grip_sub = nh->subscribe<std_msgs::Float64>("/claw_grip_controller/command", 1, &Rover_Cmd_State::claw_grip_callback, this, transportHints);
//     claw_rot_speed_sub = nh->subscribe<std_msgs::Float64>("/claw_rotate_controller/command", 1, &Rover_Cmd_State::claw_rot_speed_callback, this, transportHints);
// }

// void Rover_Cmd_State::cmd_vel_callback(const geometry_msgs::Twist::ConstPtr &msg) {

//     drive_x = msg->linear.x;
//     drive_y = msg->linear.y;
//     emit drive_x_changed();
//     emit drive_y_changed();
//     emit cmd_vel_changed();
// }

// void Rover_Cmd_State::arm_lower_callback(const std_msgs::Float64::ConstPtr &msg) {
//     arm_lower = msg->data;
//     emit arm_lower_changed();
// }
// void Rover_Cmd_State::arm_upper_callback(const std_msgs::Float64::ConstPtr &msg) {
//     arm_upper = msg->data;
//     emit arm_upper_changed();
// }
// void Rover_Cmd_State::arm_rotation_callback(const std_msgs::Float64::ConstPtr &msg) {
//     arm_rotation = msg->data;
//     emit arm_rotation_changed();
// }
// void Rover_Cmd_State::claw_grip_callback(const std_msgs::Float64::ConstPtr &msg) {
//     claw_grip = msg->data;
//     emit claw_grip_changed();
// }
// void Rover_Cmd_State::claw_rot_speed_callback(const std_msgs::Float64::ConstPtr &msg) {
//     claw_rot_speed = msg->data;
//     emit claw_rot_speed_changed();
// }

// float Rover_Cmd_State::get_drive_x() const {
//     return drive_x;
// }

// float Rover_Cmd_State::get_drive_y() const {
//     return drive_y;
// }
// float Rover_Cmd_State::get_arm_lower() const {
//     return arm_lower;
// }
// float Rover_Cmd_State::get_arm_upper() const {
//     return arm_upper;
// }
// float Rover_Cmd_State::get_arm_rotation() const {
//     return arm_rotation;
// }
// float Rover_Cmd_State::get_claw_grip() const {
//     return claw_grip;
// }
// float Rover_Cmd_State::get_claw_rot_speed() const {
//     return claw_rot_speed;
// }

// QObject * Rover_Cmd_State::qml_instance(QQmlEngine *engine, QJSEngine *script_engine) {
//     Q_UNUSED(engine);
//     Q_UNUSED(script_engine);
//
//     if(instance == NULL) {
//         instance = new Rover_Cmd_State();
//     }
//     return instance;
// }

// // because C++ is retarded
// Rover_Cmd_State * Rover_Cmd_State::instance = NULL;
