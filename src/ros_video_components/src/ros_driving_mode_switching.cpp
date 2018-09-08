#include "ros_video_components/ros_driving_mode_switching.hpp"

#define RECT_X 0
#define RECT_Y 0
#define RECT_WIDTH RECT_X*40
#define RECT_HEIGHT 150
#define MAXDATA 100
#define MAXNUM 5
#define NUMCOLOR 3
#define GREEN 4
#define YELLOW 2
#define RED 1
#define HASH MAXDATA/MAXNUM
#define TOO_WEAK MAXDATA/20

ROS_Driving_Mode_Switching::ROS_Driving_Mode_Switching(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/rover/driving_mode_switching/"),
    ros_ready(false),
    a(0),
    data(50) {
}

void ROS_Driving_Mode_Switching::setup(ros::NodeHandle * nh) {

    signal_pub = nh->advertise<std_msgs::Float32>(
        "/rover/driving_mode_switching/", //Post to this topic
         1,
         true
    );

    ros_ready = true;
    //ROS_INFO("Setup of video component complete");
}


void ROS_Driving_Mode_Switching::paint(QPainter *painter){
    //do nothing because gui is done in main_window.qml
}

void  ROS_Driving_Mode_Switching::sendmessage() {
   std_msgs::Float32 msg;

    msg.data = 1000;
    signal_pub.publish(msg);
    //when the key 'A/S/D'pressed, a should add 1
    a++;
    ROS_INFO("value is %d",a);
    // ros::spinOnce();


}



QString ROS_Driving_Mode_Switching::get_topic() const {
    return topic_value;
}

void ROS_Driving_Mode_Switching::set_topic(const QString & new_value) {
    ROS_INFO("set_topic");
    if(topic_value != new_value) {
        topic_value = new_value;
        if(ros_ready) {
            signal_pub.shutdown();
            signal_pub = nh->advertise<std_msgs::Float32>(
               "/rover/driving_mode_switching/",
                1,
                true
            );
        }
        emit topic_changed();
    }
}







void ROS_Driving_Mode_Switching::receive_signal(const std_msgs::Float32::ConstPtr & msg){
    data = msg->data;
    ROS_INFO("Received signal message");
    update();
}
