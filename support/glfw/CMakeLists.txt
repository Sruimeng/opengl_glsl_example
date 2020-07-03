set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)
project(GLFW C)

cmake_minimum_required(VERSION 2.8.12)

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    # Until all major package systems have moved to CMake 3,
    # we stick with the older INSTALL_NAME_DIR mechanism
    # NV: Disabled to silence deprecation warning
    # cmake_policy(SET CMP0042 OLD)
endif()

set(GLFW_VERSION_MAJOR "3")
set(GLFW_VERSION_MINOR "2")
set(GLFW_VERSION_PATCH "1")
set(GLFW_VERSION_EXTRA "")
set(GLFW_VERSION "${GLFW_VERSION_MAJOR}.${GLFW_VERSION_MINOR}")
set(GLFW_VERSION_FULL "${GLFW_VERSION}.${GLFW_VERSION_PATCH}${GLFW_VERSION_EXTRA}")
set(LIB_SUFFIX "" CACHE STRING "Takes an empty string or 64. Directory where lib will be installed: lib or lib64")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF )
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_VULKAN_STATIC "Use the Vulkan loader statically linked into application" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)

if (WIN32)
    option(GLFW_USE_HYBRID_HPG "Force use of high-performance GPU on hybrid systems" OFF)
endif()

if (APPLE)
    option(GLFW_USE_CHDIR "Make glfwInit chdir to Contents/Resources" ON)
    option(GLFW_USE_MENUBAR "Populate the menu bar on first window creation" ON)
    option(GLFW_USE_RETINA "Use the full resolution of Retina displays" ON)
endif()

if (UNIX AND NOT APPLE)
    option(GLFW_USE_WAYLAND "Use Wayland for window creation" OFF)
    option(GLFW_USE_MIR     "Use Mir for window creation" OFF)
endif()

if (MSVC)
    option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC runtime library DLL" ON)
endif()
if (BUILD_SHARED_LIBS)
    set(_GLFW_BUILD_DLL 1)
endif()

add_library(glad "glad.c" "glad.h")