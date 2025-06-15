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

# 添加ImGui源文件路径
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/include/imgui)

# 添加所有ImGui源文件到列表
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# 添加ImGui头文件目录
include_directories(${IMGUI_DIR})
include_directories(${IMGUI_DIR}/backends)


add_executable(202Assignments_OpenGL ${SOURCES} ${IMGUI_SOURCES})

# 链接必要的库

target_link_libraries(202Assignments_OpenGL ${GLFW_LINK})
target_link_libraries(202Assignments_OpenGL ${ASSIMP_LIBRARIES})

if (APPLE)
    target_link_libraries(202Assignments_OpenGL "-framework OpenGL")
    target_link_libraries(202Assignments_OpenGL "-framework Cocoa")
endif()
