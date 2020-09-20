#pragma once

/*
 * Each triangle has a vertex position, texture position, texture and material property
 * A model should consist of lots of these triangle structs
 * These are then fed into the WorldObject struct and used to do OpenGL magic
 * The texture is simply the location of the texture in the texture unit
 * This must be managed manually by Bind()ing textures
 */

#include <string>

#include <glm/glm.hpp>

#include <classes/surfaces/Texture2D.cpp>
#include <classes/surfaces/Material.cpp>


struct Triangle
{
    glm::vec3 vertex_positions[3];
    glm::vec2 texture_positions[3];
    glm::vec3 normal;
    glm::vec4 color_blend;
    unsigned int texture;
    unsigned int material;
};