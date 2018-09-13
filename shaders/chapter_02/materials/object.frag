#version 330 core

struct Camera {
    vec3 position;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 vertex_normal;
in vec3 vertex_position;

out vec4 vertex_color;

uniform Camera camera;
uniform Material material;
uniform Light light;

void main()
{
    vec3 light_direction = normalize(vertex_position - light.position);
    vec3 view_direction = normalize(camera.position - vertex_position);
    vec3 reflect_direction = reflect(light_direction, normalize(vertex_normal));

    // ambient
    vec3 ambient_color = light.ambient * material.ambient;

    // diffuse
    float diffuse = max(dot(normalize(vertex_normal), -light_direction), 0.0);
    vec3 diffuse_color = light.diffuse * diffuse * material.diffuse;

    // specular
    float specular = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
    vec3 specular_color =  light.specular * specular * material.specular;

    vertex_color = vec4(ambient_color + diffuse_color + specular_color, 1.0);
}