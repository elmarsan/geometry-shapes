#pragma once

#include "math.h"

struct Material
{
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};

const Material coral{
    vec3{1.0f, 0.5f, 0.31f}, vec3{1.0f, 0.5f, 0.31f}, vec3{1.0f, 0.5f, 0.31f}, vec3{0.5f}, 32.0f,
};

const Material emerald{
    vec3{80, 200, 120},
    vec3{0.0215f, 0.1745f, 0.0215f},
    vec3{0.07568f, 0.61424f, 0.07568f},
    vec3{0.633f, 0.727811f, 0.633f},
    76.0f,
};

const Material gold{vec3{255.0f, 215.0f, 0}, vec3{0.24725f, 0.1995f, 0.0745f}, vec3{0.75164f, 0.60648f, 0.22648f},
                    vec3{0.628281f, 0.555802f, 0.366065f}, 0.4f};
