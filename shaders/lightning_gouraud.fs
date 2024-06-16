#version 330 core

in vec3 PongColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(PongColor, 1.0f);
}
