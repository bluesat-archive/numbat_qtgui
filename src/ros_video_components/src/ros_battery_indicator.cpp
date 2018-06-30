#include "ros_video_components/ros_battery_indicator.hpp" //added

#define FULL_CHARGE 33

ROS_Battery_Indicator::ROS_Battery_Indicator(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/rover/signal"),
    ros_ready(false),
    charge(33) {
}

void ROS_Battery_Indicator::setup(ros::NodeHandle * nh) {

    signal_sub = nh->subscribe(
        "/rover/signal", //TODO
        1,
        &ROS_Battery_Indicator::receive_signal,
        this
    );
    ros_ready = true;
}

/*void ROS_Battery_Indicator::paint(QPainter * painter) {
    int x = 20;
    int y = 20;
    painter->drawRect(x,y,FULL_CHARGE,15);

}*/

void ROS_Battery_Indicator::set_topic(const QString & new_value) {
    ROS_INFO("set_topic");
    if(topic_value != new_value) {
        topic_value = new_value;
        if(ros_ready) {
            signal_sub.shutdown();
            signal_sub = nh->subscribe(
                topic_value.toStdString(), //TODO
                1,
                &ROS_Battery_Indicator::receive_signal,
                this
            );
        }
        emit topic_changed();
    }
}

QString battery_indicator::get_topic() const {
    return topic_value;
}

void battery_indicator::
        receive_signal(const std_msgs::Float32::ConstPtr & msg) {
    charge = msg->charge;
    ROS_INFO("Received signal message");
    update();
}

ROS_Battery_Indicator * ROS_Battery_Indicator::instance = NULL;

