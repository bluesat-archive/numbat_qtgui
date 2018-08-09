#include "ros_video_components/ros_camera_switching.hpp"
#include <QKeyEvent>

ROS_Camera_Switching::ROS_Camera_Switching(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/owr/control/availableFeeds"),
    ros_ready(false){

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

    //pub = node.advertise<owr_messages::hea>("/owr/heading",1,true);
    change_feed();
    ROS_INFO("Setup of camera switching component is complete");

}

void ROS_Camera_Switching::receive_feeds(const owr_messages::activeCameras::ConstPtr &msg){
    QColor RED = QColor::fromRgb(255, 0, 0);        //RED indicate camera is not connected
    QColor GREEN = QColor::fromRgb(128, 255, 0);    //GREEN indicates camera is turned on
    QColor ORANGE = QColor::fromRgb(255, 165, 0);   //ORANGE indicates that a camera is connected

    for( int i = 0; i < NUM_CAMERAS; i++){
        cam_colours[i] = QColor::fromRgb(255, 0, 0);
    }

   bool on;
   for( int j = 0; j < NUM_CAMERAS ; j++){
        for(int k = 0; k < msg->num; k++){
            if(msg->cameras[k].stream == j){
                on = msg->cameras[k].on;
                if(!on) cam_colours[j] = ORANGE;
                if(on) cam_colours[j] = GREEN;
            }
        }
   }

    update();
}
void ROS_Camera_Switching::change_feed(){
    ROS_INFO("I GOT HERE!");
   // pub.publish
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
