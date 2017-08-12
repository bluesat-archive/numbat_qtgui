#include "ros_coord_bearing/ros_coord_bearing.hpp"

ROSCoordBearing::ROSCoordBearing(QQuickItem *parent) : QQuickPaintedItem(parent)
{
  x = y = 0.0;
  bearing = -360.0;
}

// display readouts
void ROSCoordBearing::paint(QPainter *painter)
{
  // generate text content
  QString x_text = "X: " + QString::number(x, 'f', 3) + "\n";
  QString y_text = "Y: " + QString::number(y, 'f', 3) + "\n";
  QString bearing_text = "Bearing: " + QString::number(bearing, 'f', 3);
  QString text = x_text + y_text + bearing_text;

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

// get coordinates and bearing input for display
// intended for backend use
void ROSCoordBearing::input(double coord_x, double coord_y, double degree)
{
  x = coord_x;
  y = coord_y;
  bearing = degree;
  qDebug() << "Coordinates and bearing readings updated";
}
