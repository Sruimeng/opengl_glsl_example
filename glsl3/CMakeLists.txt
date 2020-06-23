add_executable(glsl3 glad.c main.cpp)

target_link_libraries(glsl3 glfw ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
