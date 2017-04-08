##############################################################################
# CMake
##############################################################################
cmake_minimum_required(VERSION 2.8.3)
project(timer)

##############################################################################
# Catkin
##############################################################################
find_package(catkin REQUIRED COMPONENTS
  qt_build roscpp sensor_msgs image_transport)
include_directories(include ${catkin_INCLUDE_DIRS})
catkin_package(
    CATKIN_DEPENDS qt_build roscpp sensor_msgs image_transport
    INCLUDE_DIRS include
    LIBRARIES Timer
)

##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically
# included via the dependency ca ll in package.xml
find_package(Qt5 COMPONENTS Core Gui Qml Quick Widgets REQUIRED)

##############################################################################
# Sections
##############################################################################

file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/timer/*.hpp)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################
add_library(Timer ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
qt5_use_modules(Timer Quick Core Widgets)
target_link_libraries(Timer ${QT_LIBRARIES} ${catkin_LIBRARIES})
target_include_directories(Timer PUBLIC include)
