#pragma once

/*
 * This struct stores textures and allows accessing them by ID
 * The WorldObject handles passing textures into shaders
 */

#include <vector>

#include <classes/surfaces/Texture2D.cpp>


struct TextureHandler
{
    //Store Textures
    std::vector<Texture2D*> texture_vector;

    //Add a new texture
    void AddTexture(Texture2D *texture)
    {
        texture_vector.push_back(texture);
    }

    //Remove a texture by index
    void RemoveTexture(unsigned int ID)
    {
        texture_vector.erase(texture_vector.begin() + ID);
    }

    //Find texture by index
    Texture2D GetTexture(unsigned int ID)
    {
        return *texture_vector[ID];
    }
};