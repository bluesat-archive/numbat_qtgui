#ifndef ROVER_CMD_STATE_H
#define ROVER_CMD_STATE_H

//QT
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

//ROS
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>

class Rover_Cmd_State : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(Rover_Cmd_State)
    Q_PROPERTY(float drive_x READ get_drive_x NOTIFY drive_x_changed)
    Q_PROPERTY(float drive_y READ get_drive_y NOTIFY drive_y_changed)
    Q_PROPERTY(float arm_upper READ get_arm_upper NOTIFY arm_upper_changed)
    Q_PROPERTY(float arm_lower READ get_arm_lower NOTIFY arm_lower_changed)
    Q_PROPERTY(float arm_rotation READ get_arm_rotation NOTIFY arm_rotation_changed)
    Q_PROPERTY(float claw_rot_speed READ get_claw_rot_speed NOTIFY claw_rot_speed_changed)
    Q_PROPERTY(float claw_grip READ get_claw_grip NOTIFY claw_grip_changed)

    public:
        Rover_Cmd_State(QObject *parent = 0);
        void setup(ros::NodeHandle * nh);
        float get_drive_x() const;
        float get_drive_y() const;
        float get_arm_lower() const;
        float get_arm_upper() const;
        float get_arm_rotation() const;
        float get_claw_rot_speed() const;
        float get_claw_grip() const;

        // make it a singelton
        static QObject * qml_instance(QQmlEngine * engine, QJSEngine * scriptEngine);
        static Rover_Cmd_State * instance;

    signals:
        void drive_x_changed();
        void drive_y_changed();
        void cmd_vel_changed();
        void arm_lower_changed();
        void arm_upper_changed();
        void arm_rotation_changed();
        void claw_rot_speed_changed();
        void claw_grip_changed();

    public slots:

    private:

        //ROS
        ros::NodeHandle * nh;
        ros::Subscriber  cmd_vel_sub;
        ros::Subscriber  arm_lower_sub;
        ros::Subscriber  arm_upper_sub;
        ros::Subscriber  arm_rotation_sub;
        ros::Subscriber  claw_rot_speed_sub;
        ros::Subscriber  claw_grip_sub;

        // ROS Callbacks
        void cmd_vel_callback(const geometry_msgs::Twist::ConstPtr & msg);
        void arm_lower_callback(const std_msgs::Float64::ConstPtr & msg);
        void arm_upper_callback(const std_msgs::Float64::ConstPtr & msg);
        void arm_rotation_callback(const std_msgs::Float64::ConstPtr & msg);
        void claw_grip_callback(const std_msgs::Float64::ConstPtr & msg);
        void claw_rot_speed_callback(const std_msgs::Float64::ConstPtr & msg);

        // Values
        float drive_x;
        float drive_y;
        float arm_lower;
        float arm_upper;
        float arm_rotation;
        float claw_rot_speed;
        float claw_grip;


};

#endif // ROVER_CMD_STATE_H
