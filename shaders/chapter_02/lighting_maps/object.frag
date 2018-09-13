#version 330 core

struct Camera {
    vec3 position;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Camera camera;
uniform Material material;
uniform Light light;

in vec3 vertex_normal;
in vec3 vertex_position;
in vec2 vertex_uv;

out vec4 vertex_color;

void main() {
    vec3 light_direction = normalize(vertex_position - light.position);
    vec3 view_direction = normalize(camera.position - vertex_position);
    vec3 reflect_direction = reflect(light_direction, normalize(vertex_normal));

    // ambient
    vec3 ambient_color = light.ambient * texture(material.diffuse, vertex_uv).rgb;

    // diffuse
    float diffuse = max(dot(normalize(vertex_normal), -light_direction), 0.0);
    vec3 diffuse_color = light.diffuse * diffuse * texture(material.diffuse, vertex_uv).rgb;

    // specular
    float specular = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
    vec3 specular_color =  light.specular * specular * texture(material.specular, vertex_uv).rgb;

    vertex_color = vec4(ambient_color + diffuse_color + specular_color, 1.0);
}
