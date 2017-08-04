#ifndef ROS_COORD_BEARING_HPP
#define ROS_COORD_BEARING_HPP

#include <QObject>
#include <ros/ros.h>
#include <QPainter>
#include <QString>
#include <QQuickPaintedItem>

class ROSCoordBearing : public QQuickPaintedItem
{
  Q_OBJECT
  public:
    ROSCoordBearing(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    void input(double coord_x, double coord_y, double degree);

  private:
    double x;
    double y;
    double bearing;
};

#endif // ROS_COORD_BEARING_HPP
