cmake_minimum_required(VERSION 2.8.3)
project(ros_coord_bearing)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS
    qt_build roscpp tf sensor_msgs geometry_msgs
)
include_directories(include ${catkin_INCLUDE_DIRS})
catkin_package(
    CATKIN_DEPENDS qt_build roscpp tf sensor_msgs geometry_msgs
    INCLUDE_DIRS include
    LIBRARIES ROSCoordBearing
)

##############################################################################
# Qt Environment
##############################################################################

find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)

##############################################################################
# Sections
##############################################################################

file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/ros_coord_bearing/*.hpp)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################
add_library(ROSCoordBearing ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
qt5_use_modules(ROSCoordBearing Quick Core)
target_link_libraries(ROSCoordBearing ${QT_LIBRARIES} ${catkin_LIBRARIES})
target_include_directories(ROSCoordBearing PUBLIC include)
