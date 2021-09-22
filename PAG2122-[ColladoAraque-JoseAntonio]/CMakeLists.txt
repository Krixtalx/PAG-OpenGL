cmake_minimum_required(VERSION 3.20)
project(PAG)

set(CMAKE_CXX_STANDARD 20)

add_executable(PAG main.cpp Renderer.cpp Renderer.h)

# El primer parámetro es el nombre del ejecutable. El resto son los nombres de
# las bibliotecas adicionales a enlazar
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(PAG PRIVATE GLEW::GLEW PRIVATE glfw)
