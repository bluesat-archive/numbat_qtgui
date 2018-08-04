#include "ros_video_components/keyboard_event_capture.hpp"
#include <QDebug>

Keyboard_Event_Capture::Keyboard_Event_Capture(QObject *parent) :
    QObject(parent){
    qDebug() << "Keyboard Event Capture setup";
}

void Keyboard_Event_Capture::keyPressEvent(QKeyEvent *key)
{
  switch (key->key())
  {
    case Qt::Key_Space : qDebug() << "Space is pressed";
  }
  qDebug() << "A key is pressed";
}

