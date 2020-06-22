aux_source_directory(. DIR_LIB_SRCS)

message(${DIR_LIB_SRCS})

add_executable(glsl1 glad.c main.cpp)

target_link_libraries(glsl1 glfw ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
