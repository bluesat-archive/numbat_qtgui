#ifndef PWM_READER_HPP
#define PWM_READER_HPP

class PWM_Reader : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(Example_Widget)


  public:
        PWM_Reader(QObject *parent = 0);
        void setup(ros::NodeHandle * nh);


    //make it a singleton
    static QObject * qml_instance(QQmlEngine * engine, QJSEngine * scriptEngine);
        static PWM_Reader * instance;
    signals:


  public slots:

    private:
        ros::NodeHandle * nh;
};

#endif // PWM_READER_HPP
