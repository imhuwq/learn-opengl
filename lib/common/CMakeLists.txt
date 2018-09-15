include_directories(include)

add_library(common src/shader.cpp src/camera.cpp src/mesh.cpp)
target_link_libraries(common glfw glad stb glm assimp)
