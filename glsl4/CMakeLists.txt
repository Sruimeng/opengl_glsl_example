add_executable(glsl4 glad.c main.cpp)

target_link_libraries(glsl4 glfw ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
