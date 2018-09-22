/*
 * Date Started: 25/07/16
 * Original Author: Harry J.E Day
 * Editors:
 * Purpose: C++ code representation of the QML package
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2017
 */
#ifndef OWR_ROS_COMPONENTS_H
#define OWR_ROS_COMPONENTS_H

#include <QQmlExtensionPlugin>


class OWR_ROS_Components : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "bluesat.owr")

    public:
        void registerTypes(const char * url);
};

#endif // OWR_ROS_COMPONENTS_H
