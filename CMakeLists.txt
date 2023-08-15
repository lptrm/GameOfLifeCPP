cmake_minimum_required(VERSION 3.12)

project(GameOfLifeCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DGLFW_INCLUDE_NONE)

set(VENDOR_INCLUDES vendor/glad/include vendor/glfw/include vendor/imgui
                    vendor/imgui/backends)
set(VENDOR_LINKS vendor/glad/build/bin vendor/glfw/build/src
                 vendor/imgui/bin/ImGui)
set(SOURCES src/Application.cpp src/Universe.cpp)
set(VENDOR_SOURCES
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp)
include_directories(${VENDOR_INCLUDES} src)
link_directories(${VENDOR_LINKS})

add_executable(Application ${SOURCES} ${VENDOR_SOURCES})
target_link_libraries(Application Glad.a glfw3.a libImGui.a)
