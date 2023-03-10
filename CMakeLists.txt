cmake_minimum_required(VERSION 3.10)
project(stonefish_mvp)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  geometry_msgs
  nav_msgs
  sensor_msgs
  std_msgs
  std_srvs
  roscpp
  roslib
  tf
  tf_conversions
  pcl_ros
  pcl_conversions
  image_transport
  controller_manager
  rosgraph_msgs
)

# set(ENV{PKG_CONFIG_PATH} "/home/lin/develop/ros/stonefish_ws/sim/stonefish/install/lib/pkgconfig")
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(Stonefish REQUIRED stonefish>=1.3.0)

# SET(Stonefish_DIR /home/lin/develop/ros/stonefish_ws/sim/stonefish/install/lib/cmake/Stonefish)
find_package(Stonefish REQUIRED 1.3.0)
message(STATUS "Stonefish library status:")
message(STATUS "    config: ${Stonefish_DIR}")
message(STATUS "    version: ${Stonefish_VERSION}")
message(STATUS "    libraries: ${Stonefish_LIBRARIES}")
message(STATUS "    include path: ${Stonefish_INCLUDE_DIRS}")

add_message_files(
  FILES
  Int32Stamped.msg
  ThrusterState.msg
  BeaconInfo.msg
)

add_service_files(
  FILES
  SonarSettings.srv
  SonarSettings2.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(${Stonefish_CFLAGS})

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES stonefish_mvp
  CATKIN_DEPENDS geometry_msgs
                 nav_msgs
                 sensor_msgs
                 std_msgs
                 std_srvs
                 roscpp
                 roslib
                 tf
                 tf_conversions
		             message_runtime
                 pcl_conversions
                 pcl_ros
                 image_transport
                 controller_manager
								 # mvp_msgs
                 rosgraph_msgs
	# DEPENDS Stonefish
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Stonefish_INCLUDE_DIRS}
)

link_directories(
  ${Stonefish_LIBRARY_DIRS}
)

#Library
add_library(${PROJECT_NAME}
	src/ROSInterface.cpp
	src/ROSSimulationManager.cpp
	src/ROSScenarioParser.cpp
	src/ROSControlInterface.cpp
)
add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS})
# target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${Stonefish_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} Stonefish::Stonefish)

#Universal simulators with XML parser
add_executable(parsed_simulator src/parsed_simulator.cpp
	src/ROSInterface.cpp
	src/ROSSimulationManager.cpp
	src/ROSScenarioParser.cpp
	src/ROSControlInterface.cpp
  src/Options.cpp
)
# target_link_libraries(parsed_simulator ${catkin_LIBRARIES} ${Stonefish_LIBRARIES} ${PROJECT_NAME})
target_link_libraries(parsed_simulator ${catkin_LIBRARIES} Stonefish::Stonefish ${PROJECT_NAME})

add_executable(parsed_simulator_nogpu src/parsed_simulator_nogpu.cpp
	src/ROSInterface.cpp
	src/ROSSimulationManager.cpp
	src/ROSScenarioParser.cpp
	src/ROSControlInterface.cpp
  src/Options.cpp
)
# target_link_libraries(parsed_simulator_nogpu ${catkin_LIBRARIES} ${Stonefish_LIBRARIES} ${PROJECT_NAME})
target_link_libraries(parsed_simulator_nogpu ${catkin_LIBRARIES} Stonefish::Stonefish ${PROJECT_NAME})
