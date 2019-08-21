cmake_minimum_required(VERSION 3.15)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third-party)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
add_executable(OpenGL src/main.cpp src/Shader.cpp include/Shader.h include/Logger.h src/Mesh.cpp include/Mesh.h include/ObjParser.h src/Camera.cpp include/Camera.h)

# Adding GLFW3
target_include_directories(OpenGL PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(OpenGL glfw ${OPENGL_LIBRARY} GLEW imgui)