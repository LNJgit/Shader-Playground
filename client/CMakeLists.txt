cmake_minimum_required(VERSION 3.10)
project(shader-playground LANGUAGES C CXX)

# ─── C++ Standard ─────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─── Output Directories ───────────────────────────────────────────────────────
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${OUTPUT_DIR})  # executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${OUTPUT_DIR})  # static libs (.a, .lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${OUTPUT_DIR})  # shared libs (.dll, .so)

# ─── Source Files ─────────────────────────────────────────────────────────────
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)

# ─── Include Directories ──────────────────────────────────────────────────────
include_directories(
    external/glfw/include
    external/glad/include
    external/imgui
    external/imgui/backends
    external/glm
    external/tinyobjloader
    src
)

# ─── GLFW ─────────────────────────────────────────────────────────────────────
add_subdirectory(external/glfw)

# ─── GLAD (single .c file) ────────────────────────────────────────────────────
add_library(glad STATIC external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)

# ─── ImGui ────────────────────────────────────────────────────────────────────
file(GLOB IMGUI_SRC
    external/imgui/*.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC external/imgui external/imgui/backends)

# ─── Link Everything ──────────────────────────────────────────────────────────
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad imgui)

# ─── Platform-Specific OpenGL Linking ─────────────────────────────────────────
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
elseif (UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl GL X11 pthread Xrandr Xi Xxf86vm Xcursor)
endif()
