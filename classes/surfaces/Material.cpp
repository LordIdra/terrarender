#pragma once

/*
 * Materials have a set of characteristics that dictate how light reflects off them
 * The material struct is passed into the fragment shader
 * and included in the final colour calculations
 */

#include <glm/glm.hpp>


struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float reflective;
};