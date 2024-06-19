#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 PongColor;

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light 
{
    vec3 position;
    vec3 color;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() 
{
   gl_Position = projection * view * model * vec4(aPos, 1.0f);
   
   vec3 Normal = normal * aNormal;

   vec3 FragPos = vec3(model * vec4(aPos, 1.0));

   // Ambient
   vec3 ambient = light.ambient * material.ambient;

   // Diffuse
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(light.position - FragPos);
   float diff = max(dot(norm, light.position), 0.0);
   vec3 diffuse = light.diffuse * (diff * material.diffuse);

   // Specular
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = light.specular * (spec * material.specular);

   // Phong lightning model
   PongColor = ambient + diffuse + specular;
}
