#version 330 core

in vec3 normal;
in vec3 vertex_position;

out vec4 out_color;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;

void main()
{
    vec3 light_direction = normalize(vertex_position - light_position);
    vec3 view_direction = normalize(view_position - vertex_position);
    vec3 reflect_direction = reflect(light_direction, normalize(normal));

    // ambient
    float ambient_strength = 0.1;
    vec3 ambient_color = ambient_strength * light_color;

    // diffuse
    float diffuse = max(dot(normalize(normal), -light_direction), 0.0);
    vec3 diffuse_color = diffuse * light_color;

    // specular
    float specular_strength = 0.5f;
    float specular = pow(max(dot(view_direction, reflect_direction), 0.0), 32);
    vec3 specular_color = specular_strength * specular * light_color;

    out_color = vec4((ambient_color + diffuse_color + specular_color) * object_color, 1.0);
}