/*
 * DirectionLights act as a light source with a position
 * Their influence over a fragment is calculated according to
 * how sharply the light reflects off that fragment
 */

#include <glm/glm.hpp>


struct DirectionLight {
    glm::vec3 direction;
    glm::vec3 diffuse;
    glm::vec3 specular;
};