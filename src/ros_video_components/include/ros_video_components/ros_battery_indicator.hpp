#ifndef ROS_BATTERY_INDICATOR_HPP
#define ROS_BATTERY_INDICATOR_HPP

//QT
#include <QQuickPaintedItem>
#include <QPainter>
#include <QObject>

//ROS
#include <ros/ros.h>
#include <std_msgs/Float32.h>


class  ROS_Battery_Indicator: public QQuickPaintedItem {
    //make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)

    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Battery_Indicator(QQuickItem * parent = 0);

        //void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh);

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();

    private:
        void receive_signal(const std_msgs::Float32::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Subscriber signal_sub;
        QString topic_value;
        bool ros_ready;

    int charge; //the battery charge
};


#endif // BATTERY_INDICATOR_HPP

