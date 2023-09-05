cmake_minimum_required(VERSION 3.12)

project(GameOfLifeCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DGLFW_INCLUDE_NONE)

set(VENDOR_INCLUDES vendor/glad/include vendor/glfw/include vendor/imgui
                    vendor/imgui/backends vendor/glm vendor)
set(SOURCE_INCLUDES src src/utils/OpenGL_Abstractions src/utils/Events
                    src/utils/Camera)
set(VENDOR_LINKS vendor/glad/build/bin vendor/glfw/build/src
                 vendor/imgui/bin/ImGui)
set(SOURCES
    src/Application.cpp
    src/Universe.cpp
    src/Window.cpp
    src/LayerStack.cpp
    src/Layer_ImGui.cpp
    src/Layer_Universe.cpp
    src/Input.cpp
    src/utils/OpenGL_Abstractions/Shader.cpp
    src/utils/OpenGL_Abstractions/Renderer.cpp
    src/utils/OpenGL_Abstractions/Texture.cpp
    src/utils/OpenGL_Abstractions/VertexArray.cpp
    src/utils/OpenGL_Abstractions/VertexBuffer.cpp
    src/utils/OpenGL_Abstractions/IndexBuffer.cpp
    src/utils/OpenGL_Abstractions/InstanceBuffer.cpp
    src/utils/Camera/OrthographicCamera.cpp
    src/utils/Camera/OrthographicCameraController.cpp)
set(VENDOR_SOURCES
    vendor/stb_image/stb_image.cpp
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp)
include_directories(${VENDOR_INCLUDES} ${SOURCE_INCLUDES})
link_directories(${VENDOR_LINKS})

add_executable(Application ${SOURCES} ${VENDOR_SOURCES})
target_link_libraries(Application Glad.a glfw3.a libImGui.a)
