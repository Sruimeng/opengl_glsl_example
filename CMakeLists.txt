cmake_minimum_required(VERSION 3.0.0)
project(glsl_example VERSION 0.1.0)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

set(LINK_DIR ${PROJECT_SOURCE_DIR}/lib64)
link_directories(${LINK_DIR})
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
add_subdirectory(toy)
add_subdirectory(support)

add_subdirectory(glsl1)


# add_subdirectory(glsl2)


# add_subdirectory(glsl3)
# add_subdirectory(glsl4)
# add_subdirectory(glsl5)
# add_subdirectory(glsl6)
# add_subdirectory(glsl7)
