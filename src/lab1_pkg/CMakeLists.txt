cmake_minimum_required(VERSION 3.8)
project(lab1_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

add_library(my_component SHARED src/my_component.cpp)
target_include_directories(my_component PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
ament_target_dependencies(my_component rclcpp rclcpp_components)
rclcpp_components_register_nodes(my_component "lab1_pkg::MyComponent")

install(TARGETS my_component
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin
)

ament_package()

add_executable(my_lifecycle_node src/my_lifecycle_node.cpp)
target_include_directories(my_lifecycle_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(my_lifecycle_node rclcpp rclcpp_lifecycle)

install(TARGETS my_lifecycle_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)
