#ifndef LEARN_OPENGL_MESH_H
#define LEARN_OPENGL_MESH_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "common/shader.h"

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(const vector<Vertex> &vertices, const vector<unsigned int> &indices, const vector<Texture> &textures);

    void Draw(Shader shader);

private:
    unsigned int VAO, VBO, EBO;

    void SetupMesh();
};

#endif //LEARN_OPENGL_MESH_H
