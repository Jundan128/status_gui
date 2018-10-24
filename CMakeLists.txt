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

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp message_generation std_msgs
)

set (status_gui_SRCS src/status_gui/status.cpp)
set (status_gui_HDRS include/status_gui/status.h)
set (status_gui_UIS src/status_gui/status.ui)

include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/..
  ${catkin_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
