#include "ros_coord_bearing/ros_coord_bearing.hpp"

ROSCoordBearing::ROSCoordBearing(QQuickItem *parent) : QQuickPaintedItem(parent)
{
  x = y = 0.0;
  bearing = 0.0;
}

// display readouts
void ROSCoordBearing::paint(QPainter *painter)
{
  QString x_text = "X: " + QString::number(x) + "\n";
  QString y_text = "Y: " + QString::number(y) + "\n";
  QString bearing_text = "Bearing: " + QString::number(bearing);
  QString text = x_text + y_text + bearing_text;
  QFont text_font("Sans Serif", 10, QFont::Normal);
  QFont title_font("Sans Serif", 10, QFont::Normal);
  QRect border = QRect(0, 0, 180, 90);
  QRect text_bound = QRect(5, 5, 170, 80);
  painter->setPen(Qt::green);
  painter->setFont(text_font);
  painter->drawText(text_bound, Qt::AlignLeft | Qt::AlignBottom, text);
  painter->setFont(title_font);
  painter->drawText(text_bound, Qt::AlignTop, "Coordinates and Bearing");
  painter->drawRect(border);
}

// get coordinates and bearing input for display
// intended for backend use
void ROSCoordBearing::input(double coord_x, double coord_y, double degree)
{
  x = coord_x;
  y = coord_y;
  bearing = degree;
  qDebug() << "Coordinates and bearing readings updated";
}
