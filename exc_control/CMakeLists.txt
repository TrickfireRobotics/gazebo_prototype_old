cmake_minimum_required(VERSION 2.8.3)
project(exc_control)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs ${SFML_LIBRARIES})

catkin_package()

install(DIRECTORY config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

include_directories(include ${catkin_INCLUDE_DIRS})
link_directories(${SFML_LIBRARIES})

add_executable(driver_station src/DriverStation.cpp)
target_link_libraries(driver_station ${catkin_LIBRARIES} sfml-system sfml-window sfml-graphics)
#add_dependencies(driver_station exc_control_generate_messages_cpp)

add_executable(twist_to_motors src/TwistToMotors.cpp)
target_link_libraries(twist_to_motors ${catkin_LIBRARIES})
#add_dependencies(twist_to_motors exc_control_generate_messages_cpp)
