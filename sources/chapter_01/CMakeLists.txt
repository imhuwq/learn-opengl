include_directories(utils)

set(SOURCES "")
list(APPEND SOURCES utils/shader.cpp)

add_executable(cha01_creating_a_window creating_a_window.cpp)
target_link_libraries(cha01_creating_a_window glfw ${GLFW_LIBRARIES} glad)

add_executable(cha01_hello_triangle hello_triangle.cpp)
target_link_libraries(cha01_hello_triangle glfw ${GLFW_LIBRARIES} glad)

add_executable(cha01_shaders shaders.cpp ${SOURCES})
target_link_libraries(cha01_shaders glfw ${GLFW_LIBRARIES} glad)

add_executable(cha01_textures textures.cpp ${SOURCES})
target_link_libraries(cha01_textures glfw ${GLFW_LIBRARIES} glad stb)
