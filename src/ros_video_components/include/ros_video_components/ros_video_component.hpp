#ifndef ROS_VIDEO_COMPONENT_H
#define ROS_VIDEO_COMPONENT_H

//QT
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

//ROS
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>


class ROS_Video_Component : public QQuickPaintedItem {
    //make this a Qt Widget
    Q_OBJECT
    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Video_Component(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);

    private:
        void receive_image(const sensor_msgs::Image::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        image_transport::Subscriber image_sub;

        // Used for buffering the image
        QImage * current_image;
        uchar * current_buffer;
};

#endif // ROS_VIDEO_COMPONENT_H
