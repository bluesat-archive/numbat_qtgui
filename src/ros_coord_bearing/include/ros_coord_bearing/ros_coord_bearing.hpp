#ifndef ROS_COORD_BEARING_HPP
#define ROS_COORD_BEARING_HPP

#include <QObject>
#include <ros/ros.h>
#include <QPainter>
#include <QString>
#include <QQuickPaintedItem>

#include <nav_msgs/OccupancyGrid.h>
#include <tf/transform_listener.h>
#include <tf/message_filter.h>
#include <geometry_msgs/Vector3.h>
#include <message_filters/subscriber.h>
#include <angles/angles.h>
#include <time.h>

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

    // path subscriber
    ros::NodeHandle nh;
    //ros::Subscriber pathSubscriber;
    //nav_msgs::Path navPath;

    // transform stuffs
    message_filters::Subscriber<nav_msgs::OccupancyGrid> mapSubscriber;
    tf::TransformListener tfListener;
    //tf::StampedTransform transform;
    tf::MessageFilter<nav_msgs::OccupancyGrid> tfFilter;
    tf::StampedTransform currPosition;

    // convert a transform to coordinates and bearing for display
    void convert(tf::Transform curr);
    // Callback for the map updates
    void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& gridData);

};

#endif // ROS_COORD_BEARING_HPP
