#include "ros_coord_bearing/ros_coord_bearing.hpp"

ROSCoordBearing::ROSCoordBearing(QQuickItem *parent) : QQuickPaintedItem(parent)
{
  x = y = 0.0;
  bearing = 0.0;
}

// display readouts
void ROSCoordBearing::paint(QPainter *painter)
{
  // TODO: convert readings to string
  QString text = "";
  QFont text_font("Sans Serif", 12, QFont::Normal);
  QFont title_font("Sans Serif", 10, QFont::Normal);
  QRect border = QRect(0, 0, 200, 80);
  painter->setPen(Qt::green);
  painter->setFont(text_font);
  painter->drawText(border, Qt::AlignLeft | Qt::AlignBottom, text);
  painter->setFont(title_font);
  painter->drawText(border, Qt::AlignTop, "Coordinates and Bearing");
  painter->drawRect(border);
}

// get coordinates and bearing input for display
void input(double coord_x, double coord_y, double degree)
{
  this.x = coord_x;
  this.y = coord_y;
  this.bearing = degree;
  qDebug() << "Coordinates and bearing readings obtained";
}
