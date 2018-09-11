#version 330 core

out vec4 out_color;

in vec2 uv;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    out_color = mix(texture(texture0, uv), texture(texture1, uv), 0.2);
}