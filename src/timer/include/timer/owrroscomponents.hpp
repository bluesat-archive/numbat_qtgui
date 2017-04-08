#ifndef OWRROSCOMPONENTS_HPP
#define OWRROSCOMPONENTS_HPP

#include <QQmlExtensionPlugin>
#include <QtQml>

class OwrRosComponents : public QQmlExtensionPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "bluesat.owr")

  public:
      void registerTypes(const char * url);
};

#endif // OWRROSCOMPONENTS_HPP
