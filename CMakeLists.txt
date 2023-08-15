cmake_minimum_required(VERSION 3.12)

project(GameOfLifeCPP)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(
  -DGLFW_INCLUDE_NONE
  )

set(VENDOR_INCLUDES
  vendor/glad/include
  vendor/glfw/include
  vendor/imgui
  vendor/imgui/backends
  )
set(VENDOR_LINKS
vendor/glad/build/bin
vendor/glfw/build/src
vendor/imgui/build/bin
  )
set(SOURCES
  src/Application.cpp
  src/Universe.cpp
  )
include_directories(
  ${VENDOR_INCLUDES}
  src
  )
link_directories(
  ${VENDOR_LINKS}
  )

add_executable(Application ${SOURCES})
target_link_libraries(
  Application
  Glad.a
  glfw3.a
  libImGui.a
  opengl32
  User32
  Gdi32
  Shell32
  )
set_target_properties(Application PROPERTIES LINK_FLAGS "-static")
