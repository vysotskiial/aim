cmake_minimum_required(VERSION 3.1)
project(aim VERSION 1.0)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(aim src/aim.cpp src/aim_board.cpp)

target_include_directories(aim PRIVATE include ${GLUT_INCLUDE_DIRS})
target_link_libraries(aim ${GLUT_LIBRARY} ${OPENGL_LIBRARIES})
