#ifndef ROS_CAMERA_SWITCHING_H
#define ROS_CAMERA_SWITCHING_H

//QT
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

#include <QObject>

//ROS
#include <ros/ros.h>
#include "owr_messages/activeCameras.h"

#define NUM_CAMERAS 8

class ROS_Camera_Switching : public QQuickPaintedItem {
    //make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Camera_Switching(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);
        void change_feed();

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();

    private:
        void receive_feeds(const owr_messages::activeCameras::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Subscriber available_feeds;
        QString topic_value;
        bool ros_ready;

        // Used changing camera colours
        QColor cam_colours[NUM_CAMERAS];
    protected:
        //void keyPressEvent(QKeyEvent *k) override;

};
#endif // ROS_CAMERA_SWITCHING_H
