#ifndef OWR_ROS_COMPONENTS_HPP
#define OWR_ROS_COMPONENTS_HPP

#include <QQmlExtensionPlugin>
#include <QtQml>

class Owr_Ros_Components : public QQmlExtensionPlugin
{
  Q_OBJECT

  public:
      void registerTypes(const char * uri);
};

#endif // OWR_ROS_COMPONENTS_HPP
