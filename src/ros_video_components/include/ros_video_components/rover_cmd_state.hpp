#ifndef ROVER_CMD_STATE_H
#define ROVER_CMD_STATE_H

//QT
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

//ROS
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

class Rover_Cmd_State : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(Rover_Cmd_State)
    Q_PROPERTY(float drive_x READ get_drive_x NOTIFY drive_x_changed)
    Q_PROPERTY(float drive_y READ get_drive_y NOTIFY drive_y_changed)
    public:
        Rover_Cmd_State(QObject *parent = 0);
        void setup(ros::NodeHandle * nh);
        float get_drive_x() const;
        float get_drive_y() const;

        // make it a singelton
        static QObject * qml_instance(QQmlEngine * engine, QJSEngine * scriptEngine);
        static Rover_Cmd_State * instance;

    signals:
        void drive_x_changed();
        void drive_y_changed();
        void cmd_vel_changed();

    public slots:

    private:

        //ROS
        ros::NodeHandle * nh;
        ros::Subscriber  cmd_vel_sub;
        void cmd_vel_callback(const geometry_msgs::Twist::ConstPtr & msg);

        // Values
        float drive_x;
        float drive_y;


};

#endif // ROVER_CMD_STATE_H
