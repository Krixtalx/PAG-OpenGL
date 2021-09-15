cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp Renderer.cpp Renderer.h)

# El primer parámetro es el nombre del ejecutable. El resto son los nombres de
# las bibliotecas adicionales a enlazar
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(untitled PRIVATE GLEW::GLEW PRIVATE glfw)
