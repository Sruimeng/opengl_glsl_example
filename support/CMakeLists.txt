if( UNIX )
  # On Unix-like systems, shared libraries can use the soname system.
  set(GLFW_LIB_NAME glfw)
else()
  set(GLFW_LIB_NAME glfw3)
endif()
# Filter out warnings that cause problems with GLFW.
if( WARNINGS_AS_ERRORS AND (USING_GNU_CXX OR USING_CLANG_CXX))
  string( REPLACE "-Wdeclaration-after-statement" "" filtered_c_flags ${CMAKE_C_FLAGS} )
  string( REPLACE "-Wsign-compare" "" filtered_c_flags ${filtered_c_flags} )
  push_variable( CMAKE_C_FLAGS "${filtered_c_flags} -Wno-format-truncation -Wno-deprecated" )
endif()
add_subdirectory( GLFW )
set_property( TARGET glfw PROPERTY C_STANDARD 99 )
if( WARNINGS_AS_ERRORS AND (USING_GNU_CXX OR USING_CLANG_CXX))
  pop_variable( CMAKE_C_FLAGS )
endif()

add_subdirectory( glad )
