#include "ros_video_components/ros_battery_indicator.hpp"

#define RECT_X 10
#define RECT_Y 10
#define FULL_CHARGE 33
#define GREEN (FULL_CHARGE / 3) * 2
#define YELLOW FULL_CHARGE / 3
#define INDICATOR_HEIGHT 15
#define NOB_X RECT_X + FULL_CHARGE
#define NOB_Y RECT_Y + (RECT_Y / 2)
#define NOB_WIDTH 4
#define NOB_HEIGHT 5
#define TEXT_X RECT_X + FULL_CHARGE + ((RECT_X/2) + 1)
#define TEXT_Y RECT_Y + 12
#define BAR_WIDTH 1

ROS_Battery_Indicator::ROS_Battery_Indicator(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/rover/batttery"),
    ros_ready(false),
    charge(33) {
}

void ROS_Battery_Indicator::setup(ros::NodeHandle * nh) {

    signal_sub = nh->subscribe(
        "/rover/battery", //TODO
        1,
        &ROS_Battery_Indicator::receive_signal,
        this
    );
    ros_ready = true;
}

void ROS_Battery_Indicator::paint(QPainter * painter) {
    painter->setPen(Qt::white);
    painter->drawRect(RECT_X, RECT_Y, FULL_CHARGE, INDICATOR_HEIGHT); //Draws outer rectangle
    QLinearGradient linearGradient(0, 0, 100, 100);
    linearGradient.setColorAt(0.0, Qt::black);
    painter->setBrush(linearGradient);
    painter->drawRect(NOB_X, NOB_Y, NOB_WIDTH, NOB_HEIGHT);  //Draws it at the end of the rectangle

    float charge_p = charge; //Done to easily be able to adjust values of charge from subscriber
    float bat = 0; //Used to limit how far the battery meter can if there is too much charge
    if (charge_p > FULL_CHARGE) {
        linearGradient.setColorAt(0.0, Qt::red);
        bat = FULL_CHARGE;
    } else if (charge_p > GREEN) {
        linearGradient.setColorAt(0.0, Qt::green);
        bat = charge_p;
    } else if (charge_p > YELLOW) {
        linearGradient.setColorAt(0.0, Qt::yellow);
        bat = charge_p;
    } else {
        linearGradient.setColorAt(0.0, Qt::red);
        bat = charge_p;
    }
    painter->setBrush(linearGradient);  //Setting the right color
    painter->drawRect(RECT_X, RECT_Y, bat, INDICATOR_HEIGHT);  //Draws bar showing charge

    linearGradient.setColorAt(0.0, Qt::black);
    painter->setBrush(linearGradient);
    painter->drawRect(RECT_X + YELLOW, RECT_Y, 1, INDICATOR_HEIGHT);  //Draws a bar on the indicator
    painter->drawRect(RECT_X + GREEN, RECT_Y, 1, INDICATOR_HEIGHT);   //Draws a bar on the indicator

    char percentage[6];
    charge_p = (charge_p / 33) * 100;
    sprintf(percentage, "%d%%", (int) charge_p);
    percentage[5] = '\0';
    painter->drawText(TEXT_X, TEXT_Y, percentage);  //Draws battery percentage
}

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

QString ROS_Battery_Indicator::get_topic() const {
    return topic_value;
}

void ROS_Battery_Indicator::
        receive_signal(const std_msgs::Float32::ConstPtr & msg) {
    charge = msg->data;
    ROS_INFO("Received battery message");
    update();
}

