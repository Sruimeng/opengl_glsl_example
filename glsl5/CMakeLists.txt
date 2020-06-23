add_executable(glsl5 glad.c main.cpp)

target_link_libraries(glsl5 glfw ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
