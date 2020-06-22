add_executable(offscreen glad.c toojpeg.cpp main.cpp)

target_link_libraries(offscreen glfw ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
