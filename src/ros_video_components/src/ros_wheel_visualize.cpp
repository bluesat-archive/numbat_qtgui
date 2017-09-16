#include "ros_video_components/ros_wheel_visualize.hpp"

#define RECT_X 5
#define RECT_Y 100
#define RECT_WIDTH RECT_X*40
#define RECT_HEIGHT 150
#define RADIUS 50
#define TRILENGTH 20

ROS_Wheel_Visualize::ROS_Wheel_Visualize(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    topic_value("/rover/wheel"),
    ros_ready(false),
    data(50) {
}

void ROS_Wheel_Visualize::setup(ros::NodeHandle * nh) {
    
    wheel_sub = nh->subscribe("/rover/wheel", 1, &ROS_Wheel_Visualize::receive_message,this);
    ros_ready = true;
    ROS_INFO("Setup of wheel video component complete");
}


//ROS_Wheel_Visualize::
void ROS_Wheel_Visualize::paint(QPainter * painter) {
    
	int numOfWheelBox = 4;
	int x = RECT_X;
	int y = RECT_Y;
	int width = RECT_WIDTH;
	int height = RECT_HEIGHT;
    int centerx = 60;
    int centery = 60;
    QLinearGradient linearGradient(0, 0, 100, 100);
    painter->setBrush(linearGradient);
    //I think I need to call four times instead of using a for loop in here.
    painter->drawEllipse(QPointF(centerx,centery), RADIUS, RADIUS);

    qreal curr_pointx = centerx+RADIUS*cos(data);
    qreal curr_pointy = centery+RADIUS*sin(data);
    painter->drawPoint(QPointF(x, y));
    static const QPointF points[3] = {
        QPointF(curr_pointx+TRILENGTH/2,curr_pointy-TRILENGTH/(2*1.73)),
        QPointF(curr_pointx-TRILENGTH/2,curr_pointy-TRILENGTH/(2*1.73)),
        QPointF(curr_pointx,curr_pointy+TRILENGTH*1.73)
    };

    //QPolygon polygon;
    //drawing a equilibrium triangle
    //polygon << QPoint(curr_pointx+TRILENGTH/2,curr_pointy-(TRILENGTH/(2*1.73))
    //                  << QPoint(curr_pointx-TRILENGTH/2,curr_pointy-(TRILENGTH/(2*1.73))
    //                            <<QPoint(curr_pointx,curr_pointy+TRILENGTH*1.73)
    //Qt:GlobalColor =
    painter->drawPolygon(points, 3,Qt::WindingFill);
    //for(int i=0; i<numOfWheelBox;i++){
    //    painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
    //    painter->drawEllipse(80+i, 80+i, 240, 240);//int x int y width and height
    //    painter->drawRect(x, y, width - 1, height - 1);
    //}
    //QPolygon polygon;   // Using Polygon class, to draw the triangle
    //polygon << QPoint(0,-40) << QPoint(25,40) << QPoint(-25,40);
    //painter->drawPolygon(polygon);  // Draw a triangle on a polygonal model
}

void ROS_Wheel_Visualize::set_topic(const QString & new_value) {
	ROS_INFO("set_topic");
    if(topic_value != new_value) {
        topic_value = new_value;
        if(ros_ready) {
            wheel_sub.shutdown();
            wheel_sub = nh->subscribe(topic_value.toStdString(),1,&ROS_Wheel_Visualize::receive_message,this);
        }
        emit topic_changed();
    }
}

QString ROS_Wheel_Visualize::get_topic() const {
    return topic_value;
}

void ROS_Wheel_Visualize::receive_message(const std_msgs::Float32::ConstPtr & msg){
	data = msg->data;
	ROS_INFO("Received wheel message");
	update();
}
