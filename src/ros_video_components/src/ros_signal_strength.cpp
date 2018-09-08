/*
 * Date Started: 11/02/17
 * Original Author: Sajid Anower
 * Editors:
 * Purpose: Widget to display signal strength of the antenna
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2017
 */
#include "ros_video_components/ros_signal_strength.hpp"

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

ROS_Signal_Strength::ROS_Signal_Strength(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/rover/signal"),
    ros_ready(false),
    data(50) {
}

void ROS_Signal_Strength::setup(ros::NodeHandle * nh) {

    signal_sub = nh->subscribe(
        "/rover/signal", // TODO
        1,
        &ROS_Signal_Strength::receive_signal,
        this
    );
    ros_ready = true;
}

void ROS_Signal_Strength::paint(QPainter * painter) {
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

void ROS_Signal_Strength::set_topic(const QString & new_value) {
    ROS_INFO("set_topic");
    if (topic_value != new_value) {
        topic_value = new_value;
        if (ros_ready) {
            signal_sub.shutdown();
            signal_sub = nh->subscribe(
                topic_value.toStdString(), // TODO
                1,
                &ROS_Signal_Strength::receive_signal,
                this
            );
        }
        emit topic_changed();
    }
}

QString ROS_Signal_Strength::get_topic() const {
    return topic_value;
}

void ROS_Signal_Strength::
        receive_signal(const std_msgs::Float32::ConstPtr & msg) {
    data = msg->data;
    ROS_INFO("Received signal message");
    update();
}
