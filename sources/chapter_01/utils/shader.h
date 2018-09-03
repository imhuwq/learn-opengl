#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
    unsigned int ID;

    Shader(const GLchar *vertex_path, const GLchar *fragment_path);

    void Use();

    void SetBool(const string &name, bool value) const;

    void SetInt(const string &name, int value) const;

    void SetFloat(const string &name, float value) const;
};

#endif //LEARN_OPENGL_SHADER_H
