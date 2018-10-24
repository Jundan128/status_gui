cmake_minimum_required(VERSION 2.8.3)

project(status_gui)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  message_generation
  std_msgs
)

#tambahan untuk Subscribe
#add_message_files(FILES Pose.msg)
add_message_files(FILES Battery.msg)
#add_message_files(FILES BatteryState.msg)

generate_messages(DEPENDENCIES std_msgs)


if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  find_package(Qt5Widgets REQUIRED)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
endif()

#catkin_python_setup()

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rqt_gui rqt_gui_cpp 
  message_generation std_msgs
)

set (status_gui_SRCS src/status_gui/status.cpp)
set (status_gui_HDRS include/status_gui/status.h)
set (status_gui_UIS src/status_gui/status.ui)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  qt5_wrap_cpp(status_gui_MOCS ${status_gui_HDRS})
  qt5_wrap_ui(status_gui_UIS_H ${status_gui_UIS})
else()
  qt4_wrap_cpp(status_gui_MOCS ${status_gui_HDRS})
  qt4_wrap_ui(status_gui_UIS_H ${status_gui_UIS})
endif()

include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/..
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  ${status_gui_SRCS}
  ${status_gui_MOCS}
  ${status_gui_UIS_H}
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
else()
  target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
endif()
