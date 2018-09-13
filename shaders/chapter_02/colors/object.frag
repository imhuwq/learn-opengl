#version 330 core

out vec4 out_color;

uniform vec3 object_color;
uniform vec3 light_color;

void main()
{
    out_color = vec4(light_color * object_color, 1.0);
}