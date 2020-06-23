add_executable(glsl7 glad.c main.cpp)

target_link_libraries(glsl7 glfw ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
