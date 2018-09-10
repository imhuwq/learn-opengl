#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_uv;

out vec3 color;
out vec2 uv;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(in_position, 1.0);
    color = in_color;
    uv = in_uv;
}