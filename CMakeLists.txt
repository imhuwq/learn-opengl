cmake_minimum_required(VERSION 3.10)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)

add_subdirectory(lib/glad)
include_directories(lib/glad/include)

add_subdirectory(lib/stb)
include_directories(lib/stb/include)

add_subdirectory(lib/glm)
include_directories(lib/glm/include)

add_subdirectory(lib/assimp)
include_directories(lib/assimp/include)

add_subdirectory(lib/common)
include_directories(lib/common/include)

add_subdirectory(sources)
