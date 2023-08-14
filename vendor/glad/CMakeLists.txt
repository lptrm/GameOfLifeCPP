
cmake_minimum_required(VERSION 3.15)

project(Glad)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES "src/glad.c")
file(GLOB HEADERS "include/glad/glad.h" "include/KHR/khrplatform.h")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    include
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GLCORE_PLATFORM_WINDOWS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE KHRONOS_STATIC)
    target_compile_options(${PROJECT_NAME} PRIVATE -w)
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    $<$<CONFIG:Debug>:GLCORE_DEBUG>
    $<$<CONFIG:Release>:GLCORE_RELEASE>
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GLCORE_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GLCORE_RELEASE)
endif()
