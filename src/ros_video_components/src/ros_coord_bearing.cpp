#include "ros_video_components/ros_coord_bearing.hpp"

ROSCoordBearing::ROSCoordBearing(QQuickItem *parent) : QQuickPaintedItem(parent),
          nh(), mapSubscriber(nh, "map", 1), tfFilter(mapSubscriber, tfListener, "base_link", 1)
{
  latitude = longitude = 0.0;
  bearing = 0.0;
  timer = new QTimer(this);
  tfFilter.registerCallback(boost::bind(&ROSCoordBearing::mapCallback, this, _1));
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start();
}

// display readouts
void ROSCoordBearing::paint(QPainter *painter)
{
  // generate text content
  QString lat_text = "X: " + QString::number(latitude, 'f', 3) + "\n";
  QString long_text = "Y: " + QString::number(longitude, 'f', 3) + "\n";
  QString bearing_text = "Bearing: " + QString::number(bearing, 'f', 3);
  QString text = lat_text + long_text + bearing_text;

  // set font
  QFont text_font("Sans Serif", 10, QFont::Bold);
  QFont title_font("Sans Serif", 6, QFont::Bold);

  // set border
  QRect border = QRect(0, 10, 140, 50);
  QRect text_bound = QRect(5, 0, 130, 60);

  // draw background
  QBrush brush(Qt::gray, Qt::SolidPattern);
  painter->fillRect(border, brush);
  painter->setPen(Qt::blue);
  painter->drawRect(border);

  // draw text
  painter->setFont(title_font);
  painter->drawText(text_bound, Qt::AlignLeft | Qt::AlignTop, "CO-ORDS");
  painter->setFont(text_font);
  painter->drawText(text_bound, Qt::AlignLeft | Qt::AlignBottom, text);
}

// convert a transform to coordinates and bearing for display
void ROSCoordBearing::convert(tf::Transform curr)
{

  tf::Vector3 vector = curr.getOrigin();
  latitude = (double) vector.getX();
  longitude = (double) vector.getY();

  tf::Quaternion rotation = curr.getRotation();
  double radian = tf::getYaw(rotation);
  bearing = angles::to_degrees(radian);

  qDebug() << "lat = " << latitude << ", long = " << longitude << ", bearing = " << bearing << endl;
}

// assume "map" is the starting location, "base_link" is the current location
//void ROSCoordBearing::mapCallback(const std_msgs::Float32::ConstPtr& data) {
void ROSCoordBearing::mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& data) {
  // map here is not topic, but frame id of target frame - where does it come from?
  //qDebug() << "got into callback" << endl;
  tfListener.lookupTransform("map", "base_link", ros::Time(), currPosition);
  ROSCoordBearing::convert(currPosition);
}
