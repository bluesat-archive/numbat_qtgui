#include <QTimer>
#include "gui/main_application.hpp"

Main_Application::Main_Application() {

}

void Main_Application::run() {

  // this loads the qml file we are about to create
  this->load(QUrl(QStringLiteral("qrc:/main_window.qml")));

  // Setup a timer to get the application's idle loop
  QTimer * timer  = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(main_loop()));
  timer->start(0);

}

void Main_Application::main_loop() {

  ros::spinOnce();

}
