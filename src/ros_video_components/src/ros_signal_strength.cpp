#include "ros_video_components/ros_signal_strength.hpp"

#define RECT_X
#define RECT_Y
#define RECT_WIDTH
#define RECT_HEIGHT
#define HASH 20
#define MAX_STRENGTH 100

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
	
	int data = 70;
     //painter->drawImage(QPoint(5,0), *(this->current_image));
    //ROS_INFO("DRAW FUNCTION IS BEING CALLED\n");
    //painter->drawArc(0, 0, 100, 10, 3, 10);
	int x = 5;
	int y = 100;
	int width = 200;
	int height = 150;

	//QPainter::drawRect(x, y, width, height);
	painter->drawRect(x, y, width, height);
	/*draw 4 more rectangles. the base of each would be
	x+y. **MORE EXPERIMENTATION NEEDED ON THIS ONE**
	num/25 rectangles*/
	
	int num = data/HASH;
	ROS_INFO("num is %d\n",num);
	int i = 0;
	//y -= x;
	//int barWidth = width/numBars;
	int barWidth = width/4;
	int barHeight = height/4;
	for(i = 0; i < num; i++){
		painter->drawRect(x, y, barWidth, barHeight);
		x += barWidth;
		//width += 5;
		barHeight += 20;
	}
	
    //if(current_image) {
    //    painter->drawImage(QPoint(0,0), *(this->current_image));
    //}
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
