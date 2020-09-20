/*
 * SpotLights act as a light source with a position and direction
 * Their influence over a fragment is calculated according to
 * how sharply the light reflects off that fragment
 * They stop influencing fragments at a certain radius
 * known as the cutoff distance
 */

#include <glm/glm.hpp>


struct SpotLight {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 cutoff;
    glm::vec3 diffuse;
    glm::vec3 specular;
};