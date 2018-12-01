#ifndef E_STOP_JOINTS_WIDGET_H
#define E_STOP_JOINTS_WIDGET_H
//QT
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QQmlExtensionPlugin>

#include <ros/ros.h>
#include <std_msgs/Float64.h>

class E_Stop_Joints_Widget : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(E_Stop_Joints_Widget)
    Q_PROPERTY(bool press READ getPress WRITE setPress NOTIFY Pressed)


    public:
        E_Stop_Joints_Widget(QObject *parent = 0);
        void setup(ros::NodeHandle * nh);
        bool getPress() const;
        void setPress(const bool &new_value);


        //make it a singleton
        static QObject * qml_instance(QQmlEngine * engine, QJSEngine * scriptEngine);
        static E_Stop_Joints_Widget * instance;

    signals:
    void Pressed();

    public slots:

    private:
        //ros::NodeHandle * nh;
        ros::Publisher pub;
        bool press;
};
#endif // E_STOP_JOINTS_WIDGET_H
