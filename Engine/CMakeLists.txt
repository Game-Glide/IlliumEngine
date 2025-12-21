set(SOURCE_DIR "./src")
file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.cpp"
	"${SOURCE_DIR}/*.c"
    "${SOURCE_DIR}/*.h"
)
set(LIB_INCLUDE_GLFW "vendor/GLFW/glfw3.h")
set(LIB_INCLUDE_GLFW_NATIVE "vendor/GLFW/glfw3native.h")
set(LIB_INCLUDE_KHR "vendor/KHR/khrplatform.h")
set(LIB_GLAD_C "vendor/glad.c")
set(LIB_GLAD_H "vendor/glad/glad.h")

set(LIB_SOURCES ${LIB_INCLUDE_GLFW}
	${LIB_INCLUDE_GLFW_NATIVE}
	${LIB_INCLUDE_KHR}
	${LIB_GLAD_C}
	${LIB_GLAD_H}
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

# Add source to this project's executable.
include_directories("./include/")
include_directories("./vendor/")
add_executable(IlliumEngine ${LIB_SOURCES} ${SOURCES})
set_property(TARGET IlliumEngine PROPERTY C_STANDARD 99)
set_property(TARGET IlliumEngine PROPERTY C_STANDARD_REQUIRED ON)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET IlliumEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(IlliumEngine glfw)
