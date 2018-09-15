#include <cmath>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>

#include "common/shader.h"
#include "common/camera.h"
#include "common/model.h"

static float delta_time = 0.0f;
static float last_frame = 0.0f;
static int window_width = 800;
static int window_height = 600;
static bool first_mouse = true;
static float last_mouse_x = float(window_width) / 2.0f;
static float last_mouse_y = float(window_height) / 2.0f;
static Camera *camera_ptr;

void InitializeGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void CreateGLFWWindow(GLFWwindow *&window, int width, int height) {
    window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InitializeGLAD() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

void FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void SetupViewPort(GLFWwindow *window) {
    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
}

void ProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera_ptr->ProcessKeyboard(Camera_Movement::FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera_ptr->ProcessKeyboard(Camera_Movement::BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera_ptr->ProcessKeyboard(Camera_Movement::LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera_ptr->ProcessKeyboard(Camera_Movement::RIGHT, delta_time);
}

void CleanScreen() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    auto current_mouse_x = (float) xpos;
    auto current_mouse_y = (float) ypos;

    if (first_mouse) {
        last_mouse_x = current_mouse_x;
        last_mouse_y = current_mouse_y;
        first_mouse = false;
        return;
    }

    float xoffset = current_mouse_x - last_mouse_x;
    float yoffset = last_mouse_y - current_mouse_y;
    last_mouse_x = current_mouse_x;
    last_mouse_y = current_mouse_y;

    camera_ptr->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera_ptr->ProcessMouseScroll((float) yoffset);
}

int main() {
    InitializeGLFW();

    GLFWwindow *window;
    CreateGLFWWindow(window, window_width, window_height);

    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
    camera_ptr = &camera;

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    InitializeGLAD();

    SetupViewPort(window);

    string model_path = "models/nanosuit/nanosuit.obj";
    Model object_model(model_path);

    Shader object_shader("shaders/chapter_03/loading_model/object.vert", "shaders/chapter_03/loading_model/object.frag");

    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    glm::vec3 light_position(1.0f, 1.0f, 1.0f);
    glm::vec3 light_color(1.0f);

    while (!glfwWindowShouldClose(window)) {
        auto current_frame = (float) glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        ProcessInput(window);

        CleanScreen();

        object_shader.Use();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        object_shader.SetMat4("model", model);

        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), (float) window_width / (float) window_height, 0.1f, 100.0f);
        object_shader.SetMat4("view", view);

        object_shader.SetMat4("projection", projection);

        object_model.Draw(object_shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
