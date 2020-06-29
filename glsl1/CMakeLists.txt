aux_source_directory(. DIR_LIB_SRCS)

message(${DIR_LIB_SRCS})

add_executable(glsl1 glad.c main.cpp)

if (WIN32)
    target_link_libraries(glsl1 ${OPENGL_LIBRARIES})
else (WIN32)
  if ( USING_GNU_C AND NOT APPLE)
    target_link_libraries(glsl1 glfw ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS} )
  endif()
endif (WIN32)