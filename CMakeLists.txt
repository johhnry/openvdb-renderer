cmake_minimum_required(VERSION 3.12)

# set the project name
project(openvdb-renderer VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###############################################################
# PACKAGES
###############################################################

# Imgui
add_subdirectory(imgui)

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# OpenVDB
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/src/ext/openvdb/cmake")
find_package(OpenVDB REQUIRED)

###############################################################
# SOURCES
###############################################################

set(SOURCES
  src/main.cpp
)

###############################################################
# EXECUTABLE
###############################################################

include_directories(${PROJECT_SOURCE_DIR})

# add the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  glfw
  imgui
  OpenVDB::openvdb
)
