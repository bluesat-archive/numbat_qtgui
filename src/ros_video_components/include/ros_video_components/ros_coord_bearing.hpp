#ifndef ROS_COORD_BEARING_HPP
#define ROS_COORD_BEARING_HPP

#include <QObject>
#include <ros/ros.h>
#include <QPainter>
#include <QString>
#include <QQuickPaintedItem>

#include <nav_msgs/OccupancyGrid.h>
#include <std_msgs/Float32.h>

#include <tf/transform_listener.h>
#include <tf/message_filter.h>
#include <geometry_msgs/Vector3.h>
#include <message_filters/subscriber.h>
#include <angles/angles.h>
#include <time.h>
#include <QTimer>

/**
 * GUI widget to display the current coordinates and bearing of the rover
 * relevant to its starting position, using tf transform.
 * Tested with: publishing an OccupancyGrid msg under "/map" topic in rqt
 * 							and publishing tf transform with `static_transform_publisher`
 * 							from "map" to "base_link"
 */
class ROSCoordBearing : public QQuickPaintedItem
{
    Q_OBJECT
    public:
        ROSCoordBearing(QQuickItem *parent = 0);
        void paint(QPainter *painter);

    private:
        // display readings
        double latitude;
        double longitude;
        double bearing;

        QTimer *timer;

        // path subscriber
        ros::NodeHandle nh;

        // transform stuffs
        message_filters::Subscriber<nav_msgs::OccupancyGrid> mapSubscriber;
        tf::TransformListener tfListener;
        tf::MessageFilter<nav_msgs::OccupancyGrid> tfFilter;
        tf::StampedTransform currPosition;

        // convert a transform to coordinates and bearing for display
        void convert(tf::Transform curr);
        // Callback for the map updates
        void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& gridData);
};

#endif // ROS_COORD_BEARING_HPP
