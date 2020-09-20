#pragma once

/*
 * The lighting container is designed to be used once per program
 * It is universal - it stores and handles all lights on a scene
 * When WorldObjects are rendered, values from the lighting 
 * container will be sent to the shaders
 */

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <classes/lights/DirectionLight.cpp>
#include <classes/lights/PointLight.cpp>
#include <classes/lights/SpotLight.cpp>


struct LightingHandler
{
    //These are the main values
    //They store all lighting objects on the scene, plus global ambience
    std::vector<DirectionLight> direction_lights;
    std::vector<PointLight> point_lights;
    std::vector<SpotLight> spot_lights;
    glm::vec3 ambience = glm::vec3(0.0f, 0.0f, 0.0f);

    //Add/remove a DirectionLight
    void AddDirectionLight(DirectionLight light) {direction_lights.push_back(light);}
    void RemoveDirectionLight(unsigned int index) {direction_lights.erase(direction_lights.begin() + index);}

    //Add/remove a PointLight
    void AddPointLight(PointLight light) {point_lights.push_back(light);}
    void RemovePointLight(unsigned int index) {point_lights.erase(point_lights.begin() + index);}

    //Add/remove a SpotLight
    void AddSpotLight(SpotLight light) {spot_lights.push_back(light);}
    void RemoveSpotLight(unsigned int index) {spot_lights.erase(spot_lights.begin() + index);}

    //Set global ambience
    void SetAmbience(glm::vec3 amb) {ambience = amb;}
};