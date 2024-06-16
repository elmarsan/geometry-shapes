#version 330 core

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

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main() 
{
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
   vec3 pong = ambient + diffuse + specular;
   FragColor = vec4(pong, 1.0);
}
