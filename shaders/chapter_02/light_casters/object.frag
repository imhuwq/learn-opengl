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
    vec3 direction;
    float cutoff;
    float outer_cutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float liner;
    float quadratic;
};

uniform Camera camera;
uniform Material material;
uniform Light light;

in vec3 vertex_normal;
in vec3 vertex_position;
in vec2 vertex_uv;

out vec4 frag_color;

void main() {
    vec3 vertex_light_direction = vertex_position - light.position;
    float theta = dot(vertex_light_direction, light.direction);
    float eplison = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / eplison, 0.0, 1.0);

    float distance = length(light.position - vertex_position);
    float attenuation = 1.0 / (light.constant + light.liner * distance + light.quadratic * distance * distance);
    attenuation *= intensity;

    // ambient
    vec3 ambient_color = light.ambient * texture(material.diffuse, vertex_uv).rgb;

    if (theta > light.cutoff) {
        vec3 view_direction = normalize(camera.position - vertex_position);
        vec3 reflect_direction = reflect(vertex_light_direction, normalize(vertex_normal));

        // diffuse
        float diffuse = max(dot(normalize(vertex_normal), -vertex_light_direction), 0.0);
        vec3 diffuse_color = attenuation * light.diffuse * diffuse * texture(material.diffuse, vertex_uv).rgb;

        // specular
        float specular = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
        vec3 specular_color =  attenuation * light.specular * specular * texture(material.specular, vertex_uv).rgb;

        frag_color = vec4(ambient_color + diffuse_color + specular_color, 1.0);
    } else {
        frag_color = vec4(ambient_color, 1.0);
    }

}
