cmake_minimum_required(VERSION 2.8.3)
project(tests)


find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES tutorials
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(180 180.cpp)
target_link_libraries(180 ${catkin_LIBRARIES})

add_executable(tilting_test tilting_test.cpp)
target_link_libraries(tilting_test ${catkin_LIBRARIES})
