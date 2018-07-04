#include "ros_video_components/ros_video_component.hpp"

ROS_Video_Component::ROS_Video_Component(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    current_image(NULL),
    current_buffer(NULL),
    topic_value("/cam0"),
    ros_ready(false),
    img_trans(NULL) {

}

void ROS_Video_Component::setup(ros::NodeHandle * nh) {

    img_trans = new image_transport::ImageTransport(*nh);
    //TODO: make these parameters of the component
    image_sub = img_trans->subscribe(
          topic_value.toStdString(),
          1,
          &ROS_Video_Component::receive_image,
          this,
          image_transport::TransportHints("compressed")
    );

    ros_ready = true;
    ROS_INFO("Setup of video component complete");
}

void ROS_Video_Component::receive_image(const sensor_msgs::Image::ConstPtr &msg) {
    // check to see if we already have an image frame, if we do then we need to
    // delete it to avoid memory leaks
    if( current_image ) {
        delete current_image;
    }

    // allocate a buffer of sufficient size to contain our video frame
    uchar * temp_buffer = (uchar *) malloc(sizeof(uchar) * msg->data.size());

    // and copy the message into the buffer
    // we need to do this because QImage api requires the buffer we pass in to
    // continue to exist whilst the image is in use, but the msg and it's data will
    // be lost once we leave this context
    current_image = new QImage(
          temp_buffer,
          msg->width,
          msg->height,
          QImage::Format_RGB888 // TODO: detect the type from the message
    );

    ROS_INFO("Recieved Message");

    // We then swap out of bufer to avoid memory leaks
    if(current_buffer) {
        delete current_buffer;
        current_buffer = temp_buffer;
    }

    // finally we need to re-render the component to display the new image
    update();
}

void ROS_Video_Component::paint(QPainter * painter) {
    if(current_image) {
        painter->drawImage(QPoint(0,0), *(this->current_image));
    }
    //BRUSH COLOURS
    QBrush YELLOW(Qt::yellow, Qt::SolidPattern);    //YELLOW indicates camera is connected
    QBrush RED(Qt::red, Qt::SolidPattern);          //RED indicate camera is not connected
    QBrush GREEN(Qt::green, Qt::SolidPattern);      //GREEN indicates camera is turned on
                                                    //Note: Only the camera you can currently see is turned on (GREEN)
    //Rectangle for cam 0
    QRectF cam0(0, 50, 50, 50);
    //Qpainter->drawRoundedRect(cam0, 8, 8);
    painter->fillRect(cam0,RED);
    painter->drawText(cam0,Qt::AlignCenter,tr("0"));
    //Rectangle for cam 1
    QRectF cam1(0, 130, 50, 50);
    //painter->drawRoundedRect(cam1, 8, 8);
    painter->drawText(cam1,Qt::AlignCenter,tr("1"));
    //Rectangle for cam 2
    QRectF cam2(0, 210, 50, 50);
    //painter->drawRoundedRect(cam2, 8, 8);
    painter->drawText(cam2,Qt::AlignCenter,tr("2"));
    //Rectangle for cam 3
    QRectF cam3(0, 290, 50, 50);
    //painter->drawRoundedRect(cam3, 8, 8);
    painter->drawText(cam3,Qt::AlignCenter,tr("3"));
    //Rectangle for cam 4
    QRectF cam4(0, 370, 50, 50);
    //painter->drawRoundedRect(cam4, 8, 8);
    painter->drawText(cam4,Qt::AlignCenter,tr("4"));
    //Rectangle for cam 5
    QRectF cam5(0, 450, 50, 50);
    //painter->drawRoundedRect(cam5, 8, 8);
    painter->drawText(cam5,Qt::AlignCenter,tr("5"));
    //Rectangle for cam 6
    QRectF cam6(0, 530, 50, 50);
    //painter->drawRoundedRect(cam6, 8, 8);
    painter->drawText(cam6,Qt::AlignCenter,tr("6"));
    //Rectangle for cam 7
    QRectF cam7(0, 610, 50, 50);
    //painter->drawRoundedRect(cam7, 8, 8);
    painter->drawText(cam7,Qt::AlignCenter,tr("7"));

}

void ROS_Video_Component::set_topic(const QString & new_value) {
    if(topic_value != new_value) {
        topic_value = new_value;
        if(ros_ready) {
            image_sub.shutdown();
            image_sub = img_trans->subscribe(
                  topic_value.toStdString(),
                  1,
                  &ROS_Video_Component::receive_image,
                  this,
                  image_transport::TransportHints("compressed")
            );
        }
        emit topic_changed();
    }
}

QString ROS_Video_Component::get_topic() const {
    return topic_value;
}
