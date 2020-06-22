add_executable(glsl2 glad.c main.cpp)

target_link_libraries(glsl2 glfw ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
