#include <cmath>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>

#include <common/shader.h>
#include <common/camera.h>

float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

static float delta_time = 0.0f;
static float last_frame = 0.0f;
static int window_width = 800;
static int window_height = 600;
static bool first_mouse = true;
static float last_mouse_x = float(window_width) / 2.0f;
static float last_mouse_y = float(window_height) / 2.0f;
static Camera *camera_ptr;
static float camera_speed = 0.05f;

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

unsigned int LoadTexture(const string &texture_path) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nr_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &nr_channels, 0);
    if (data) {
        GLenum format = GL_RGB;
        if (nr_channels == 1) format = GL_RED;
        else if (nr_channels == 3) format = GL_RGB;
        else if (nr_channels == 4) format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);
    return texture;
}

void SetupObjectBuffers(unsigned int &VAO) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void SetupLightBuffers(unsigned int &VAO) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
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

    Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));
    camera_ptr = &camera;

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    InitializeGLAD();

    SetupViewPort(window);

    unsigned int object_VAO;
    SetupObjectBuffers(object_VAO);

    unsigned int light_VAO;
    SetupLightBuffers(light_VAO);

    Shader object_shader("shaders/chapter_02/lighting_maps/object.vert", "shaders/chapter_02/lighting_maps/object.frag");
    Shader light_shader("shaders/chapter_02/lighting_maps/light.vert", "shaders/chapter_02/lighting_maps/light.frag");

    unsigned int diffuse_map = LoadTexture("textures/container2.png");
    unsigned int specular_map = LoadTexture("textures/container2_specular.png");

    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    glm::vec3 light_position(1.0f, 1.0f, 1.0f);
    glm::vec3 light_color(1.0f);

    while (!glfwWindowShouldClose(window)) {
        auto current_frame = (float) glfwGetTime();
        delta_time = current_frame - last_frame;
        camera_speed = 0.1f * delta_time;

        ProcessInput(window);

        CleanScreen();

        object_shader.Use();
        object_shader.SetInt("material.diffuse", 0);
        object_shader.SetInt("material.specular", 1);
        object_shader.SetFloat("material.shininess", 32.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_map);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_map);

        object_shader.SetVec3("light.position", light_position);
        object_shader.SetVec3("light.ambient", glm::vec3(0.5f));
        object_shader.SetVec3("light.diffuse", glm::vec3(0.2f));
        object_shader.SetVec3("light.specular", glm::vec3(1.0f));

        object_shader.SetVec3("camera.position", camera.Position);

        model = glm::mat4(1.0f);
        model = glm::rotate(model, -35.0f, glm::vec3(0.0f, 1.0f, 0.0));
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), (float) window_width / (float) window_height, 0.1f, 100.0f);
        object_shader.SetMat4("model", model);
        object_shader.SetMat4("view", view);
        object_shader.SetMat4("projection", projection);

        glBindVertexArray(object_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        light_shader.Use();
        light_shader.SetVec3("light_color", light_color);

        light_position.x = 1.0f + (float) sin(glfwGetTime()) * 2.0f;
        light_position.y = (float) sin(glfwGetTime() / 2.0f) * 1.0f;
        model = glm::mat4(1.0f);
        model = glm::translate(model, light_position);
        model = glm::scale(model, glm::vec3(0.2f));
        light_shader.SetMat4("model", model);
        light_shader.SetMat4("view", view);
        light_shader.SetMat4("projection", projection);

        glBindVertexArray(light_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
