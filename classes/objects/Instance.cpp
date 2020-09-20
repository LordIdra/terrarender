#pragma once

/*
 * Instance structs describe the position properties of a WorldObject instance
 * They store offset, rotation and scale
 * At render time, this is used to create model transform matrices
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


struct Instance
{
    glm::vec3 offset;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 matrix;

    Instance(glm::vec3 offset_i, glm::vec3 rotation_i, glm::vec3 scale_i)
        : offset(offset_i),
        rotation(rotation_i),
        scale(scale_i),
        matrix(glm::mat4(1.0f))
    {
        matrix = glm::translate(matrix, offset);
        
        //Check if we're actually rotating the matrix
        //If we pass vec3(0.0f, 0.0f, 0.0f) in
        //it'll return nans
        if (rotation.x != 0.0f || rotation.y != 0.0f || rotation.z != 0.0f)
        {
            matrix = glm::rotate(matrix, glm::radians(360.0f), rotation);
        }

        matrix = glm::scale(matrix, scale);
    }

    void Translate(glm::vec3 offset_i)
    {
        offset = offset_i;
        matrix = glm::translate(matrix, offset);
    }

    void Rotate(glm::vec3 rotation_i)
    {
        rotation = rotation_i;
        matrix = glm::rotate(matrix, glm::radians(360.0f), rotation);
    }

    void Scale(glm::vec3 scale_i)
    {
        scale = scale_i;
        matrix = glm::scale(matrix, scale);
    }
};