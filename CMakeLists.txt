cmake_minimum_required(VERSION 3.0.0)
project(glsl_example VERSION 0.1.0)

message(${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)
find_package(OpenGL REQUIRED)
#find_package(glfw3 REQUIRED)
set( CMAKE_CXX_FLAGS "-std=c++11" )
# 查找当前目录下的所有源文件

# 并将名称保存到 DIR_SRCS 变量

add_subdirectory(glsl1)

#target_link_libraries(glfw)
target_link_libraries(OpenGL)
