cmake_minimum_required (VERSION 3.8)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

project ("IlliumEngine" LANGUAGES C CXX)

# Include sub-projects.
add_subdirectory ("Engine")
add_subdirectory("Lib/glfw-3.4")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)