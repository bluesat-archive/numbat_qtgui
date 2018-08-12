#include "ros_video_components/ros_camera_switching.hpp"
#include <QKeyEvent>

ROS_Camera_Switching::ROS_Camera_Switching(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/owr/control/availableFeeds"),
    camera_topic_value(),
    ros_ready(false),
    camera_number(NO_CAMERA_SELECTED)
    {

}

void ROS_Camera_Switching::setup(ros::NodeHandle * nh) {
    available_feeds = nh->subscribe(
          topic_value.toStdString(),
          1,
          &ROS_Camera_Switching::receive_feeds,
          this
    );

    for( int i = 0; i < NUM_CAMERAS; i++){
        cam_colours[i] = QColor::fromRgb(255, 0, 0);
    }

    ros_ready = true;

    control_feeds = nh->advertise<owr_messages::stream>("/owr/control/activateFeeds", 1);
    ROS_INFO("Setup of camera switching component is complete");

}

static const QColor RED = QColor::fromRgb(255, 0, 0);        //RED indicate camera is not connected
static const QColor GREEN = QColor::fromRgb(128, 255, 0);    //GREEN indicates camera is in use by us
static const QColor DARK_GREEN = QColor::fromRgb(0, 51, 0);    //GREEN indicates camera is in use
static const QColor ORANGE = QColor::fromRgb(255, 165, 0);   //ORANGE indicates that a camera is connected

void ROS_Camera_Switching::receive_feeds(const owr_messages::activeCameras::ConstPtr &msg){

    for( int i = 0; i < NUM_CAMERAS; i++){
        cam_colours[i] = RED;
    }

    bool on;
    for( int j = 0; j < NUM_CAMERAS ; j++){
        for(int k = 0; k < msg->num; k++){
            if(msg->cameras[k].stream == j){
                on = msg->cameras[k].on;
                if(!on) {
                    cam_colours[j] = ORANGE;
                } else if(on) {
                    if(j == camera_number) {
                        cam_colours[j] = GREEN;
                    } else {
                        cam_colours[j] = DARK_GREEN;
                    }
                }
            }
        }
    }

    update();
}

void ROS_Camera_Switching::set_camera_number(int cam) {
    ROS_INFO("Camera change to %d", cam);
    // disable existing feed
    owr_messages::stream msg;
    if(camera_number != NO_CAMERA_SELECTED && ros_ready) {
        msg.stream = camera_number;
        msg.on = false;
        control_feeds.publish(msg);
    }
    camera_number = cam;

    if(camera_number != NO_CAMERA_SELECTED && ros_ready) {
        msg.stream = camera_number;
        msg.on = true;
        control_feeds.publish(msg);
    }

    std::ostringstream topic_in;
    topic_in << "/cam" << cam;
    camera_topic_value = QString(topic_in.str().c_str());
    emit camera_topic_changed();
    emit camera_number_changed();
}

void ROS_Camera_Switching::paint(QPainter * painter) {

    //Rectangle for cam 0
    QRectF cam_0(20, 80, 50, 50);
    //Qpainter->drawRoundedRect(cam0, 8, 8);
    painter->fillRect(cam_0,cam_colours[0]);
    painter->drawText(cam_0,Qt::AlignCenter,tr("0"));

    //Rectangle for cam 1
    QRectF cam_1(20, 160, 50, 50);
    //painter->drawRoundedRect(cam1, 8, 8);
    painter->fillRect(cam_1,cam_colours[1]);
    painter->drawText(cam_1,Qt::AlignCenter,tr("1"));

    //Rectangle for cam 2
    QRectF cam_2(20, 240, 50, 50);
    //painter->drawRoundedRect(cam2, 8, 8);
     painter->fillRect(cam_2,cam_colours[2]);
    painter->drawText(cam_2,Qt::AlignCenter,tr("2"));

    //Rectangle for cam 3
    QRectF cam_3(20, 320, 50, 50);
    //painter->drawRoundedRect(cam3, 8, 8);
    painter->fillRect(cam_3,cam_colours[3]);
    painter->drawText(cam_3,Qt::AlignCenter,tr("3"));

    //Rectangle for cam 4
    QRectF cam_4(20, 400, 50, 50);
    //painter->drawRoundedRect(cam4, 8, 8);
    painter->fillRect(cam_4,cam_colours[4]);
    painter->drawText(cam_4,Qt::AlignCenter,tr("4"));

    //Rectangle for cam 5
    QRectF cam_5(20, 480, 50, 50);
    //painter->drawRoundedRect(cam5, 8, 8);
    painter->fillRect(cam_5,cam_colours[5]);
    painter->drawText(cam_5,Qt::AlignCenter,tr("5"));

    //Rectangle for cam 6
    QRectF cam_6(20, 560, 50, 50);
    //painter->drawRoundedRect(cam6, 8, 8);
    painter->fillRect(cam_6,cam_colours[6]);
    painter->drawText(cam_6,Qt::AlignCenter,tr("6"));

    //Rectangle for cam 7
    QRectF cam_7(20, 640, 50, 50);
    //painter->drawRoundedRect(cam7, 8, 8);
    painter->fillRect(cam_7,cam_colours[7]);
    painter->drawText(cam_7,Qt::AlignCenter,tr("7"));
}

void ROS_Camera_Switching::set_topic(const QString & new_value) {
    if(topic_value != new_value) {
        topic_value = new_value;
        if(ros_ready) {
            available_feeds.shutdown();
            available_feeds = nh->subscribe(
                  topic_value.toStdString(),
                  1,
                  &ROS_Camera_Switching::receive_feeds,
                  this
            );
        }
        emit topic_changed();
    }
}

QString ROS_Camera_Switching::get_topic() const {
    return topic_value;
}

QString ROS_Camera_Switching::get_camera_topic() const {
    return camera_topic_value;
}

int ROS_Camera_Switching::get_camera_number() const {
    return camera_number;
}
