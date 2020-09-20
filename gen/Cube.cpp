#pragma once

#include <classes/containers/WorldObject.cpp>

std::vector<Triangle> GenerateCube(glm::vec4 color, unsigned int texture, unsigned int material)
{
    std::vector<Triangle> cube_triangles;

    cube_triangles.push_back(Triangle{

        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(0.5, -0.5, 0.5),
        glm::vec3(0.5, -0.5, -0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(0.0, 1.0f, 0.0),

        color, texture, material});

    cube_triangles.push_back(Triangle{

        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(0.5, -0.5, 0.5),
        glm::vec3(-0.5, -0.5, 0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(0.0, 1.0),

        glm::vec3(0.0, 1.0f, 0.0),

        color, texture, material});


    cube_triangles.push_back(Triangle{

        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(-0.5, 0.5, -0.5),
        glm::vec3(0.5, 0.5, -0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(0.0, 1.0f, 0.0),

        color, texture, material});

    cube_triangles.push_back(Triangle{

        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(-0.5, 0.5, -0.5),
        glm::vec3(-0.5, 0.5, 0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(0.0, 1.0f, 0.0),

        color, texture, material});


    cube_triangles.push_back(Triangle{

        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(0.5, -0.5, -0.5),
        glm::vec3(0.5, 0.5, -0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(1.0f, 0.0f, 0.0),

        color, texture, material});

    cube_triangles.push_back(Triangle{

        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(0.5, -0.5, -0.5),
        glm::vec3(0.5, -0.5, 0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(1.0f, 0.0f, 0.0),

        color, texture, material});


    cube_triangles.push_back(Triangle{

        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(-0.5, 0.5, 0.5),
        glm::vec3(-0.5, -0.5, 0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(-1.0f, 0.0f, 0.0),

        color, texture, material});

    cube_triangles.push_back(Triangle{

        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(-0.5, 0.5, 0.5),
        glm::vec3(-0.5, 0.5, -0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(-1.0f, 0.0f, 0.0),

        color, texture, material});


    cube_triangles.push_back(Triangle{

        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(-0.5, -0.5, 0.5),
        glm::vec3(-0.5, 0.5, 0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(0.0f, 0.0f, 1.0f),

        color, texture, material});
        
    cube_triangles.push_back(Triangle{

        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(-0.5, -0.5, 0.5),
        glm::vec3(0.5, -0.5, 0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(0.0f, 0.0f, 1.0f),

        color, texture, material});


    cube_triangles.push_back(Triangle{

        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(0.5, 0.5, -0.5),
        glm::vec3(0.5, -0.5, -0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(0.0f, 0.0f, -1.0f),

        color, texture, material});

    cube_triangles.push_back(Triangle{

        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(0.5, 0.5, -0.5),
        glm::vec3(-0.5, 0.5, -0.5),

        glm::vec2(0.0, 0.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),

        glm::vec3(0.0f, 0.0f, -1.0f),

        color, texture, material});


    return cube_triangles;
}