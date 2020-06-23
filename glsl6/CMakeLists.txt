add_executable(glsl6 glad.c main.cpp)

target_link_libraries(glsl6 glfw ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
