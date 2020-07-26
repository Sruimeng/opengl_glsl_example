project(glsl1)
add_executable(glsl1 main.cpp)
target_link_libraries(glsl1  tojpg toy ${OPENGL_LIBRARIES} glad glfw3)



