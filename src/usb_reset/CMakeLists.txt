##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(usb_reset)

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS qt_build roscpp)
include_directories(include ${catkin_INCLUDE_DIRS})
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything.
catkin_package(
    CATKIN_DEPENDS qt_build roscpp
    INCLUDE_DIRS include
    LIBRARIES usb_reset
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
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/usb_reset/*.hpp)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################
add_library(usb_reset ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
qt5_use_modules(usb_reset Quick Core)
target_link_libraries(usb_reset ${QT_LIBRARIES} ${catkin_LIBRARIES})
target_include_directories(usb_reset PUBLIC include)
