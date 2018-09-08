/*
 * Date Started: 8/09/18
 * Original Author: Sajid Ibne Anower
 * Editors:
 * Purpose: Widget to display voltage of the batteries
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2017, 2018
 */
#include "ros_video_components/ros_voltage_meter.hpp"

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

ROS_Voltage_Meter::ROS_Voltage_Meter(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/rover/volt"),
    ros_ready(false),
    data(50) {}

void ROS_Voltage_Meter::setup(ros::NodeHandle * nh) {
    volt_sub = nh->subscribe(
        "/rover/volt",
        1,
        &ROS_Voltage_Meter::receive_volt_val,
        this);
    ros_ready = true;
}

void ROS_Voltage_Meter::paint(QPainter * painter) {
    int x = RECT_X;
    int y = RECT_Y;
    int widthV = width(); // RECT_WIDTH;
    int heightV = height(); // RECT_HEIGHT;

    QLinearGradient linearGradient(0, 0, 100, 100);
    int num = 0;
    float hash = HASH;
    if (data >= MAXDATA) {
        num = MAXNUM;
    } else if (data <= TOO_WEAK) {
        num = 0;
        linearGradient.setColorAt(0.0, Qt::white);
        painter->setBrush(linearGradient);
    } else {
        num = (data/hash) + 1;
    }
    // draw the outer main rectangle
    painter->drawRect(x, y, widthV - 1, heightV - 1);

    int i = 0;

    int barWidth = widthV/MAXNUM;
    int barHeight = heightV/MAXNUM;
    y += ((MAXNUM-1) * heightV) /MAXNUM;
    const int increment = heightV/MAXNUM;
    if (num == 0) {
        ROS_INFO("NO SIGNAL\n");
    } else {
        for (i = 1; i <= num; i++) {
            if (num >= GREEN) {
                linearGradient.setColorAt(0.2, Qt::green);
            } else if (num >= YELLOW) {
                linearGradient.setColorAt(0.2, Qt::yellow);
            } else {
                linearGradient.setColorAt(0.2, Qt::red);
            }
            painter->setBrush(linearGradient);
            painter->drawRect(x, y, barWidth, barHeight);
            x += barWidth; // move x along
            barHeight += increment; // increase height
            y -= increment; // decrease height
        }
    }
}

void ROS_Voltage_Meter::set_topic(const QString & new_value) {
    // ROS_INFO("set_topic");
    if (topic_value != new_value) {
        topic_value = new_value;
        if (ros_ready) {
            volt_sub.shutdown();
            volt_sub = nh->subscribe(
                topic_value.toStdString(),
                1,
                &ROS_Voltage_Meter::receive_volt_val,
                this);
        }
        emit topic_changed();
    }
}

QString ROS_Voltage_Meter::get_topic() const {
    return topic_value;
}

void ROS_Voltage_Meter :: receive_volt_val(const std_msgs::Float32::ConstPtr & msg) {
    data = msg->data;
    ROS_INFO("Received voltage update");
    update();
}
