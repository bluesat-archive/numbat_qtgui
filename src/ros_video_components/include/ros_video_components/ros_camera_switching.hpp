#ifndef ROS_CAMERA_SWITCHING_H
#define ROS_CAMERA_SWITCHING_H

//QT
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>
#include <QShortcut>

#include <QObject>

//ROS
#include <ros/ros.h>
#include "owr_messages/activeCameras.h"

#define NUM_CAMERAS 8

const int NO_CAMERA_SELECTED = -1;

class ROS_Camera_Switching : public QQuickPaintedItem {
    //make this a Qt Widget
    Q_OBJECT
    /**
     * defines a qml value for the topic
     */
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    /**
     * the selected camera topic
     */
    Q_PROPERTY(QString camera_topic READ get_camera_topic NOTIFY camera_topic_changed)

    /**
     * the number of the camera
     */
    Q_PROPERTY(int camera_number READ get_camera_number WRITE set_camera_number NOTIFY camera_number_changed)


    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Camera_Switching(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

        QString get_camera_topic() const;

        int get_camera_number() const;
        void set_camera_number(int cam_num);

    signals:
        void topic_changed();
        void camera_topic_changed();
        void camera_number_changed();

    private:
        void receive_feeds(const owr_messages::activeCameras::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Subscriber available_feeds;
        ros::Publisher control_feeds;
        QString topic_value;
        QString camera_topic_value;

        bool ros_ready;

        // Used changing camera colours
        QColor cam_colours[NUM_CAMERAS];
        int camera_number;
    protected:
        //void keyPressEvent(QKeyEvent *k) override;

};
#endif // ROS_CAMERA_SWITCHING_H
