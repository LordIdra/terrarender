#pragma once

#include <classes/containers/WorldObject.cpp>

std::vector<Triangle> GenerateSquare(glm::vec4 color, unsigned int texture, unsigned int material)
{
    std::vector<Triangle> square_triangles;

    square_triangles.push_back(Triangle{

        glm::vec3(0.5, 0.5, 0.0),
        glm::vec3(-0.5, -0.5, 0.0),
        glm::vec3(-0.5, 0.5, 0.0),

        glm::vec2(1.0, 1.0),
        glm::vec2(0.0, 0.0),
        glm::vec2(0.0, 1.0),

        glm::vec3(0.0f, 0.0f, 1.0f),

        color, texture, material});

    square_triangles.push_back(Triangle{

        glm::vec3(0.5, 0.5, 0.0),
        glm::vec3(-0.5, -0.5, 0.0),
        glm::vec3(0.5, -0.5, 0.0),

        glm::vec2(1.0, 1.0),
        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(0.0f, 0.0f, -1.0f),
        
        color, texture, material});

    return square_triangles;
}