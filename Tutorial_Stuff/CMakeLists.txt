# CMakeList.txt : CMake project for Tutorial_Stuff, include source and define
# project specific logic here.
#

set(SOURCE_DIR "./src")
file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.cpp"
	"${SOURCE_DIR}/*.c"
    "${SOURCE_DIR}/*.h"
)
set(LIB_INCLUDE_GLFW "include/GLFW/glfw3.h")
set(LIB_INCLUDE_GLFW_NATIVE "include/GLFW/glfw3native.h")
set(LIB_INCLUDE_KHR "include/KHR/khrplatform.h")
set(LIB_GLAD_C "glad.c")
set(LIB_GLAD_H "include/glad/glad.h")

set(LIB_SOURCES ${LIB_INCLUDE_GLFW}
	${LIB_INCLUDE_GLFW_NATIVE}
	${LIB_INCLUDE_KHR}
	${LIB_GLAD_C}
	${LIB_GLAD_H}
)

# Add source to this project's executable.
include_directories("./include/")
add_executable (Tutorial_Stuff ${LIB_SOURCES} ${SOURCES})
set_property(TARGET Tutorial_Stuff PROPERTY C_STANDARD 99)
set_property(TARGET Tutorial_Stuff PROPERTY C_STANDARD_REQUIRED ON)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tutorial_Stuff PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(Tutorial_Stuff glfw)