//QT
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QQmlExtensionPlugin>

#include <ros/ros.h>

class EStopGeneral : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(EStopGeneral)

    public:
        EStopGeneral(QObject *parent = 0);
        void setup(ros::NodeHandle * nh);


        //make it a singleton
        static QObject * qml_instance(QQmlEngine * engine, QJSEngine * scriptEngine);
        static EStopGeneral * instance;
    signals:


    public slots:

    private:
        ros::NodeHandle * nh;
};

