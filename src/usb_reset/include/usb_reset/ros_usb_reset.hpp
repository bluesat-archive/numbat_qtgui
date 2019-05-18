/*
 * Date Started: 11/08/18
 * Original Author: Lasindu Shanil de Silva
 * Editors:
 * Purpose: Widget to create buttons to reset usb devices
 * This code is released under the MIT License. Copyright BLUEsat UNSW, 2019
 */
#ifndef ROS_USB_RESET_H
#define ROS_USB_RESET_H

//QT
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>
#include <QAbstractListModel>

#include <QObject>
#include <QList>
#include <QListView>
#include <QtQuick>
#include <QVariant>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>

//ROS
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <iostream>
#include <std_msgs/Int16.h>
#include "owr_messages/devices.h"

class ROS_Usb_Reset : public QQuickPaintedItem {
    //make this a Qt Widget
    Q_OBJECT
    // defines a qml value for the topic
    Q_PROPERTY(QString topic READ get_topic WRITE set_topic NOTIFY topic_changed)


    public:
        // Constructor, takes parent widget, which defaults to null
        ROS_Usb_Reset(QQuickItem * parent = 0);

        void paint(QPainter *painter);
        void setup(ros::NodeHandle * nh, QQmlContext *ctxt);
        Q_INVOKABLE void publish(int num);
        Q_INVOKABLE int num_devices();

    protected:

        //getters and setters
        void set_topic(const QString &new_value);
        QString get_topic() const;

    signals:
        void topic_changed();

    private:
        void receive_msg(const owr_messages::devices::ConstPtr & msg);

        // ROS
        ros::NodeHandle * nh;
        ros::Subscriber usb_sub;
        ros::Publisher usb_pub;
        QString topic_value;
        bool ros_ready;
        QQmlContext *curr_ctxt;

        // Used for storing attached devices
        std::string devices[100];
        // Holds number of attached devices
        int num;
};

#endif // ROS_USB_RESET_H