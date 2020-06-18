aux_source_directory(. DIR_LIB_SRCS)

message(${DIR_LIB_SRCS})

add_executable(glsl1 ${DIR_LIB_SRCS})

target_link_libraries(glsl1 glfw3 ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
