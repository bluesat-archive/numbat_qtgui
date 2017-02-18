##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
# TODO: change your package name
project(ros_gui_stub)

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
# TODO: ADD DEPENDENCIES THAT AREN'T IN THIS PACKAGE
find_package(catkin REQUIRED COMPONENTS qt_build roscpp sensor_msgs image_transport)
include_directories(include ${catkin_INCLUDE_DIRS})
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything.
catkin_package(
    # TODO: ADD DEPENDENCIES HERE
    CATKIN_DEPENDS qt_build roscpp sensor_msgs image_transport
    # This lets us access all subfolders of /include/
    INCLUDE_DIRS include
    # TODO: change package name
    LIBRARIES RosGuiStub
)

##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically
# included via the dependency ca ll in package.xml
find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)

##############################################################################
# Sections
##############################################################################

file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
# TODO: Modify your include libraries
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/ros_gui_stub/*.hpp)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################
# TODO: replace with your library name
add_library(RosGuiStub ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
qt5_use_modules(RosGuiStub Quick Core)
target_link_libraries(RosGuiStub ${QT_LIBRARIES} ${catkin_LIBRARIES})
target_include_directories(RosGuiStub PUBLIC include)
