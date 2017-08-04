#ifndef OWR_ROS_COMPONENTS_H
#define OWR_ROS_COMPONENTS_H

#include <QQmlExtensionPlugin>
#include <QtQml>

class OWR_ROS_Components : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "bluesat.owr");

    public:
        void registerTypes(const char * url);
};

#endif // OWR_ROS_COMPONENTS_H
