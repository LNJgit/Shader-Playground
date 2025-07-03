cmake_minimum_required(VERSION 3.10)
project(shader-playground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add source files
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/imgui
    ${CMAKE_SOURCE_DIR}/src
)

# Add external dependencies
add_subdirectory(external/glfw)

# GLAD (single file)
add_library(glad external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)

# ImGui
file(GLOB IMGUI_SRC
    external/imgui/*.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC external/imgui external/imgui/backends)

# Link everything together
target_link_libraries(${PROJECT_NAME} glfw glad imgui)

# Platform-specific
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
elseif (UNIX)
    target_link_libraries(${PROJECT_NAME} dl GL X11 pthread Xrandr Xi Xxf86vm Xcursor)
elseif (WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()
