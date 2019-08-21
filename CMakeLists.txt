cmake_minimum_required(VERSION 3.12)
project(FacialAnimation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
add_subdirectory(third-party)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
add_executable(FacialAnimation src/main.cpp src/Shader.cpp include/Shader.h include/Logger.h src/Mesh.cpp include/Mesh.h include/ObjParser.h src/Camera.cpp include/Camera.h)

# Adding GLFW3
target_include_directories(FacialAnimation PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(FacialAnimation glfw ${OPENGL_LIBRARY} GLEW imgui)