#pragma once

/*
 * The camera class maintains a 3D camera that can be rotated and translated at will
 * It will automatically calculate and supply the matrix required to
 * move world objects as needed
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Camera
{
    //Variables to store vectors that determine where the camera is and how it's orientated
    glm::vec3 camera_position = glm::vec3(0.0f, 1.0f, 2.5f);
    glm::vec3 camera_rotation = glm::vec3(-90.0f, 0.0f, 0.0f);
    glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 camera_direction = glm::vec3(0.0f, 0.0f, 1.0f);

    float screen_x;
    float screen_y;

    float near;
    float far;

    float field_of_view;

    //Default constructor
    Camera() = default;

    //Initialize parameters
    Camera(float screen_x_i, float screen_y_i, float field_of_view_i, float near_i, float far_i)
        : screen_x(screen_x_i),
        screen_y(screen_y_i),
        field_of_view(field_of_view_i),
        near(near_i),
        far(far_i)
    {
        camera_direction.x = cos(glm::radians(camera_rotation.x)) * cos(glm::radians(camera_rotation.y));
        camera_direction.y = sin(glm::radians(camera_rotation.y));
        camera_direction.z = sin(glm::radians(camera_rotation.x)) * cos(glm::radians(camera_rotation.y));

        camera_direction = glm::normalize(camera_direction);
    }

    //Sets the camera's position to the vector provided
    void SetPosition(glm::vec3 position_vector)
    {
        camera_position = position_vector;
    }

    //Sets the cameras rotation and immediately computes the resulting direction
    //Does not compute roll
    void SetDirection(glm::vec3 rotation_vector)
    {
        camera_rotation = rotation_vector;
    
        camera_direction.x = cos(glm::radians(camera_rotation.x)) * cos(glm::radians(camera_rotation.y));
        camera_direction.y = sin(glm::radians(camera_rotation.y));
        camera_direction.z = sin(glm::radians(camera_rotation.x)) * cos(glm::radians(camera_rotation.y));

        camera_direction = glm::normalize(camera_direction);
    }

    //Translates the camera by the vector provided
    void Translate(glm::vec3 position_vector)
    {
        camera_position += position_vector.x * glm::normalize(glm::cross(camera_direction, camera_up));
        camera_position += position_vector.y * camera_up;
        camera_position += position_vector.z * camera_direction;
    }

    //Rotates the camera and immediately computes the resulting direction
    //Does not compute roll
    void Rotate(glm::vec3 rotation_vector)
    {
        if (rotation_vector != glm::vec3(0.0f, 0.0f, 0.0f))
        {
            camera_rotation += rotation_vector;

            if (camera_rotation.y > 89.0f) camera_rotation.y = 89.0f;
            if (camera_rotation.y < -89.0f) camera_rotation.y = -89.0f;
            
            camera_direction.x = cos(glm::radians(camera_rotation.x)) * cos(glm::radians(camera_rotation.y));
            camera_direction.y = sin(glm::radians(camera_rotation.y));
            camera_direction.z = sin(glm::radians(camera_rotation.x)) * cos(glm::radians(camera_rotation.y));

            camera_direction = glm::normalize(camera_direction);
        }
    }

    //Returns the view matrix that objects must be multiplied by to simulate the camera
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(camera_position, camera_position + camera_direction, camera_up);
    }

    glm::mat4 GetPerspectiveMatrix()
    {
        return glm::perspective(glm::radians(field_of_view), screen_y / screen_x, near, far);
    }
};