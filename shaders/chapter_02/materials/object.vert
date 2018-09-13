#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

out vec3 vertex_normal;
out vec3 vertex_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vertex_normal = mat3(transpose(inverse(model))) * in_normal;;
    vertex_position = vec3(model * vec4(in_position, 1.0));

    gl_Position = projection * view * model * vec4(in_position, 1.0);
}