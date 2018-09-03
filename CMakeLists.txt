cmake_minimum_required(VERSION 3.10)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)

add_subdirectory(lib/glad)
include_directories(lib/glad/include)

add_subdirectory(lib/stb)
include_directories(lib/stb/include)

add_executable(learn_opengl main.cpp)
add_subdirectory(sources)
