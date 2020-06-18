cmake_minimum_required(VERSION 3.0.0)
project(glsl_example VERSION 0.1.0)


set(LINK_DIR ${PROJECT_SOURCE_DIR}/lib64)
link_directories(${LINK_DIR})
link_libraries(glfw)
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_library(glad "include/glad/glad.c")

#find_package(glfw3 REQUIRED)
set( CMAKE_CXX_FLAGS "-std=c++11" )
# 查找当前目录下的所有源文件

# 并将名称保存到 DIR_SRCS 变量

add_subdirectory(glsl1)

