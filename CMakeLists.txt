cmake_minimum_required(VERSION 3.18.1)
project(202Assignments_OpenGL VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

find_package(assimp REQUIRED)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib-arm64)
include_directories(${HEADER_DIR}/ ${LIB_DIR}/)

set(GLFW_LINK ${LIB_DIR}/libglfw.3.dylib)

set(SOURCES ${SRC_DIR}/glad.c ${SRC_DIR}/main.cpp)
add_executable(202Assignments_OpenGL ${SOURCES})

target_link_libraries(202Assignments_OpenGL ${GLFW_LINK})
target_link_libraries(202Assignments_OpenGL ${ASSIMP_LIBRARIES})

if (APPLE)
    target_link_libraries(202Assignments_OpenGL "-framework OpenGL")
    target_link_libraries(202Assignments_OpenGL "-framework Cocoa")
endif()
