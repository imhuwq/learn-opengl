#version 330 core

struct Camera {
    vec3 position;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;

    vec3 direction;
    float cutoff;
    float outer_cutoff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Camera camera;
uniform Material material;
uniform DirectionalLight direction_light;
#define NR_POINT_LIGHTS 4
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform SpotLight spot_light;

in vec3 vertex_normal;
in vec3 vertex_position;
in vec2 vertex_uv;

out vec4 frag_color;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 view_direction);

vec3 CalculatePointLight(PointLight light, vec3 view_direction);

vec3 CalculateSpotLight(SpotLight light, vec3 view_direction);

void main() {
    vec3 view_direction = normalize(camera.position - vertex_position);

    vec3 result = CalculateDirectionalLight(direction_light, view_direction);
    for (int i = 0; i < NR_POINT_LIGHTS; i ++) {
        result += CalculatePointLight(point_lights[i], view_direction);
    }
    result += CalculateSpotLight(spot_light, view_direction);

    frag_color = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 view_direction) {
    vec3 ambient_color = light.ambient * vec3(texture(material.diffuse, vertex_uv));

    float diffuse = max(dot(vertex_normal, -light.direction), 0.0);
    vec3 diffuse_color = light.diffuse * diffuse * vec3(texture(material.diffuse, vertex_uv));

    vec3 reflect_direction = reflect(light.direction, vertex_normal);
    float specular = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
    vec3 specular_color = light.specular * specular * vec3(texture(material.specular, vertex_uv));

    return (ambient_color + diffuse_color + specular_color);
}

vec3 CalculatePointLight(PointLight light, vec3 view_direction) {
    vec3 vertex_light_direction = vertex_position - light.position;

    vec3 ambient_color = light.ambient * vec3(texture(material.diffuse, vertex_uv));

    float diffuse = max(dot(vertex_normal, -vertex_light_direction), 0.0);
    vec3 diffuse_color = light.diffuse * diffuse * vec3(texture(material.diffuse, vertex_uv));

    vec3 reflect_direction = reflect(vertex_light_direction, vertex_normal);
    float specular = pow(max(dot(vertex_normal, reflect_direction), 0.0), material.shininess);
    vec3 specular_color = light.specular * specular * vec3(texture(material.specular, vertex_uv));

    float distance = length(light.position - vertex_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    return attenuation * (ambient_color + diffuse_color + specular_color);
}

vec3 CalculateSpotLight(SpotLight light, vec3 view_direction) {
    vec3 vertex_light_direction = vertex_position - spot_light.position;
    float theta = dot(vertex_light_direction, spot_light.direction);
    float eplison = spot_light.cutoff - spot_light.outer_cutoff;
    float intensity = clamp((theta - spot_light.outer_cutoff) / eplison, 0.0, 1.0);

    float distance = length(spot_light.position - vertex_position);
    float attenuation = 1.0 / (spot_light.constant + spot_light.linear * distance + spot_light.quadratic * distance * distance);
    attenuation *= intensity;

    // ambient
    vec3 ambient_color = spot_light.ambient * texture(material.diffuse, vertex_uv).rgb;

    if (theta < spot_light.cutoff) return ambient_color;
    else {
        vec3 reflect_direction = reflect(vertex_light_direction, normalize(vertex_normal));

        // diffuse
        float diffuse = max(dot(normalize(vertex_normal), -vertex_light_direction), 0.0);
        vec3 diffuse_color = attenuation * spot_light.diffuse * diffuse * texture(material.diffuse, vertex_uv).rgb;

        // specular
        float specular = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
        vec3 specular_color =  attenuation * spot_light.specular * specular * texture(material.specular, vertex_uv).rgb;

        return (ambient_color + diffuse_color + specular_color);
    }
}
