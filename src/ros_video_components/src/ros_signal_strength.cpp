#include "ros_video_components/ros_signal_strength.hpp"
/*#include <QLabel>
#include <QMainWindow>
#include <QApplication>*/

#define RECT_X 5
#define RECT_Y 100
#define RECT_WIDTH RECT_X*40
#define RECT_HEIGHT 150
#define MAXDATA 100
#define MAXNUM 5
#define NUMCOLOR 3
#define GREEN 4
#define YELLOW 2
#define RED 1
#define HASH MAXDATA/MAXNUM
#define TOO_WEAK MAXDATA/20

ROS_Signal_Strength::ROS_Signal_Strength(QQuickItem * parent) :
    QQuickPaintedItem(parent),
    current_image(NULL),
    current_buffer(NULL),
    topic_value("/cam0"),
    ros_ready(false),
    img_trans(NULL) {
}

void ROS_Signal_Strength::setup(ros::NodeHandle * nh) {

    img_trans = new image_transport::ImageTransport(*nh);
    //TODO: make these parameters of the component
    image_sub = img_trans->subscribe(
          topic_value.toStdString(),
          1,
          &ROS_Signal_Strength::receive_image,
          this,
          image_transport::TransportHints("compressed")
    );

    ros_ready = true;
    ROS_INFO("Setup of video component complete");
}

void ROS_Signal_Strength::receive_image(const sensor_msgs::Image::ConstPtr &msg) {
    // check to see if we already have an image frame, if we do then we need to
    // delete it to avoid memory leaks
    if( current_image ) {
        delete current_image;
    }

    // allocate a buffer of sufficient size to contain our video frame
    uchar * temp_buffer = (uchar *) malloc(sizeof(uchar) * msg->data.size());

    // and copy the message into the buffer
    // we need to do this because QImage api requires the buffer we pass in to
    // continue to exist whilst the image is in use, but the msg and it's data will
    // be lost once we leave this context
    current_image = new QImage(
          temp_buffer,
          msg->width,
          msg->height,
          QImage::Format_RGB888 // TODO: detect the type from the message
    );

    ROS_INFO("Recieved Message");

    // We then swap out of bufer to avoid memory leaks
    if(current_buffer) {
        delete current_buffer;
        current_buffer = temp_buffer;
    }

    // finally we need to re-render the component to display the new image
    update();
}

void ROS_Signal_Strength::paint(QPainter * painter) {
	
	int data = 3; //int data = getSignalStrength();

	int x = RECT_X;
	int y = RECT_Y;
	int width = RECT_WIDTH;
	int height = RECT_HEIGHT;

	QLinearGradient linearGradient(0, 0, 100, 100);
	int num = 0;
	float hash = HASH;
	if(data >= MAXDATA){
		num = MAXNUM;
	}else if(data <= TOO_WEAK){
		num = 0;
		linearGradient.setColorAt(0.0, Qt::white);
		painter->setBrush(linearGradient);	
	}else{
		num = (data/hash) +1;
	}
	painter->drawRect(x, y, width, height); //draw the main rectangle
	
	int i = 0;
	
	int barWidth = width/MAXNUM;
	int barHeight = height/MAXNUM;
	y += ((MAXNUM-1) * height) /MAXNUM;
	const int increment = height/MAXNUM;
	//ROS_INFO("y is %d, barHeight is %d\n",y, barHeight);
	if(num == 0){
		//print flashing "NO SIGNAL" on the screen
		/*QLabel * label = new QLabel(&mainWindow);
		label->setText("NO SIGNAL\n");
		mainWindow.show();*/
		ROS_INFO("NO SIGNAL\n");
	}else{
		for(i = 1; i <= num; i++){
		    
		    if(num >= GREEN/*(MAXNUM - (MAXNUM/NUMCOLOR))*/){
			    linearGradient.setColorAt(0.2, Qt::green);
		    }else if(num >= YELLOW/*(MAXNUM/NUMCOLOR)*/){
			    linearGradient.setColorAt(0.2, Qt::yellow);        	
		    }else{
		    	linearGradient.setColorAt(0.2, Qt::red);
		    }
		    painter->setBrush(linearGradient);
			painter->drawRect(x, y, barWidth, barHeight);
			x += barWidth; //move x along
			barHeight += increment; //increase height
			y -= increment; //decrease height
		}
	}
	
}

void ROS_Signal_Strength::set_topic(const QString & new_value) {
    if(topic_value != new_value) {
        topic_value = new_value;
        if(ros_ready) {
            image_sub.shutdown();
            image_sub = img_trans->subscribe(
                  topic_value.toStdString(),
                  1,
                  &ROS_Signal_Strength::receive_image,
                  this,
                  image_transport::TransportHints("compressed")
            );
        }
        emit topic_changed();
    }
}

QString ROS_Signal_Strength::get_topic() const {
    return topic_value;
}
