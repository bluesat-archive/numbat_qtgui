#include "ros_video_components/ros_video_component.hpp"
#include <iostream>

ROS_Video_Component::ROS_Video_Component(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    current_image(NULL),
    current_buffer(NULL),
    topic_value(),
    ros_ready(false),
    img_trans(NULL) {

}

void ROS_Video_Component::setup(ros::NodeHandle * nh) {

    img_trans = new image_transport::ImageTransport(*nh);
    //TODO: make these parameters of the componen
    if(!topic_value.isEmpty()) {
        image_sub = img_trans->subscribe(
              topic_value.toStdString(),
              1,
              &ROS_Video_Component::receive_image,
              this,
              image_transport::TransportHints("compressed")
        );
    }

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
    memcpy(temp_buffer, msg->data.data(), msg->data.size());

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
        // scale on the largest edge
        // using the algorith here: https://stackoverflow.com/questions/6565703/math-algorithm-fit-image-to-screen-retain-aspect-ratio
        float new_height, new_width;
        // which one has the largest ration
        if( (width()/height()) > (current_image->width()/current_image->height())) {
            new_width = (current_image->width() * height())/ (float) current_image->height();
            new_height = height();
        } else {
            new_width = width();
            new_height = (current_image->height() * width())/ (float)current_image->width();
        }
        painter->drawImage(QRect((width()- new_width)/2 , (height()- new_height)/2, new_width, new_height), *(this->current_image));
    } else if (topic_value.isEmpty()) {
        painter->drawText(QPoint(10,10), "No Topic Selected");
    }
    painter->drawRect(0,0,1,10);
}

void ROS_Video_Component::set_topic(const QString & new_value) {
    ROS_INFO("new value %s", new_value.toStdString().c_str());
    if(topic_value != new_value) {
        topic_value = new_value;
        if(!topic_value.isEmpty()) {
            if(ros_ready) {
                ROS_INFO("new value %s", new_value.toStdString().c_str());
                image_sub.shutdown();
                image_sub = img_trans->subscribe(
                      topic_value.toStdString(),
                      1,
                      &ROS_Video_Component::receive_image,
                      this,
                      image_transport::TransportHints("compressed")
                );
            }
        } else {
            image_sub.shutdown();
        }
        emit topic_changed();
    }
}

QString ROS_Video_Component::get_topic() const {
    return topic_value;
}
