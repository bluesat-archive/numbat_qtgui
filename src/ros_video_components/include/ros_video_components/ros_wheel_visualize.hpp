#ifndef ROS_WHEEL_VISUALIZE_H
#define ROS_WHEEL_VISUALIZE_H



#include <QQuickPaintedItem>
#include <QPainter>


#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include "owr_messages/board.h"

class ROS_Wheel_Visualize : public QQuickPaintedItem {
    Q_OBJECT
    
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    public:
        
        ROS_Wheel_Visualize(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);

        
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();

    private:
        void receive_message(const owr_messages::board::ConstPtr & msg);

        
        ros::NodeHandle * nh;
        ros::Subscriber wheel_sub;
        QString topic_value;
        bool ros_ready;
        
    double curr;
    double targ;
};
#endif
