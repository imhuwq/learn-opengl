#include "shader.h"

using namespace std;

Shader::Shader(const GLchar *vertex_path, const GLchar *fragment_path) {
    string vertex_code;
    string fragment_code;
    ifstream vertex_shader_file;
    ifstream fragment_shader_file;

    vertex_shader_file.exceptions(ifstream::failbit | ifstream::badbit);
    fragment_shader_file.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        vertex_shader_file.open(vertex_path);
        fragment_shader_file.open(fragment_path);
        stringstream vertex_shader_stream, fragment_shader_stream;
        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();
        vertex_code = vertex_shader_stream.str();
        fragment_code = fragment_shader_stream.str();
        vertex_shader_file.close();
        fragment_shader_file.close();
    } catch (ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
    }

    const char *vertex_shader_code_c = vertex_code.c_str();
    const char *fragment_shader_code_c = fragment_code.c_str();
    unsigned int vertex, fragment;
    int success;
    char vertex_info_log[512], frag_info_log[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_shader_code_c, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, vertex_info_log);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertex_info_log << "\n" << vertex_code << endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_shader_code_c, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, frag_info_log);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << frag_info_log << "\n" << fragment_code << endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, vertex_info_log);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << vertex_info_log << endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use() {
    glUseProgram(ID);
}


void Shader::SetBool(const string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::SetInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetMat4(const string &name, const glm::mat4 &value) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}