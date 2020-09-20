#pragma once

/*
 * This struct stores the materials and allows accessing them by ID
 * The WorldObject handles passing materials into shaders
 * Note that only the material addresses are stored, so materials
 * will be destroyed once the initial Material goes out of scope
 */

#include <vector>

#include <classes/surfaces/Material.cpp>


struct MaterialHandler
{
    //Vector to store Materials
    std::vector<Material*> material_vector;

    //Add a new material
    void AddMaterial(Material *material)
    {
        material_vector.push_back(material);
    }

    //Remove a material by index
    void RemoveTexture(unsigned int ID)
    {
        material_vector.erase(material_vector.begin() + ID);
    }

    //Find material by index
    Material GetMaterial(unsigned int ID)
    {
        return *material_vector[ID];
    }
};