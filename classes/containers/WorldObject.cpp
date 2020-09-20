#pragma once

/*
 * This stores data about one object composed of vertices that can be 
 * instantiated many times, and each instance can have different attributes
 * primarily offset, rotation and scale
 * The object data is stored in global VBOs, each of which store specific data of
 * ALL the WorldObjects created
 * This significantly speeds up rendering since we don't need to handle
 * as many VBOs
 */

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <classes/objects/Triangle.cpp>
#include <classes/objects/Instance.cpp>

#include <classes/containers/Shader.cpp>
#include <classes/move/Camera.cpp>

#include <classes/containers/MaterialHandler.cpp>
#include <classes/containers/TextureHandler.cpp>
#include <classes/containers/LightingHandler.cpp>


struct WorldObject
{
    //Store the IDs of the VBO
    unsigned int vbo_vertex_buffer_ID = 0;

    //Store the IDs of the VAO
    unsigned int vao_ID = 0;

    //Vector for storing instances
    std::vector<Instance> instance_vector;

    //Vertex, instance and texture count
    unsigned int vertex_count = 0;
    unsigned int instance_count = 0;

    //Stores our shader program and TextureHandler
    Shader program;
    TextureHandler texture_handler;
    LightingHandler lighting_handler;

    //Construct our triangle and vertex buffers using the supplied data
    //The triangle and vertex buffers can only be constructed once per WorldObject
    WorldObject(Shader shader, std::vector<Triangle> triangle_array, 
        TextureHandler texture_handler_in, MaterialHandler material_handler_in, LightingHandler lighting_handler_in)
        : program(shader), 
        vertex_count(triangle_array.size()*3),
        texture_handler(texture_handler_in),
        lighting_handler(lighting_handler_in)
    {
        //Vertex buffer is constructed by taking the vertex and texture positions
        //of each triangle, and appending them to a vector
        //Triangle buffer is constructed by taking the material and texture IDs
        //of each triangle, and appending them to another vector
        std::vector<float> vertex_constructor;

        for (Triangle element : triangle_array)
        {
            //Loop through all vertices in triangle
            for (int i = 0; i < 3; i++) 
            {
                //Append vertex position
                vertex_constructor.push_back(element.vertex_positions[i].x);
                vertex_constructor.push_back(element.vertex_positions[i].y);
                vertex_constructor.push_back(element.vertex_positions[i].z);

                //Append texture position
                vertex_constructor.push_back(element.texture_positions[i].x);
                vertex_constructor.push_back(element.texture_positions[i].y);

                //Append surface normal
                vertex_constructor.push_back(element.normal.x);
                vertex_constructor.push_back(element.normal.y);
                vertex_constructor.push_back(element.normal.z);

                //Append texture IDs
                vertex_constructor.push_back((float)(element.texture));

                //Get and append all material properties
                Material target_material = material_handler_in.GetMaterial(element.material);

                //Ambient
                vertex_constructor.push_back(target_material.ambient.x);
                vertex_constructor.push_back(target_material.ambient.y);
                vertex_constructor.push_back(target_material.ambient.z);

                //Diffuse
                vertex_constructor.push_back(target_material.diffuse.x);
                vertex_constructor.push_back(target_material.diffuse.y);
                vertex_constructor.push_back(target_material.diffuse.z);

                //Specular
                vertex_constructor.push_back(target_material.specular.x);
                vertex_constructor.push_back(target_material.specular.y);
                vertex_constructor.push_back(target_material.specular.z);

                //Reflective
                vertex_constructor.push_back(target_material.reflective);

                //Color blend
                vertex_constructor.push_back(element.color_blend.x);
                vertex_constructor.push_back(element.color_blend.y);
                vertex_constructor.push_back(element.color_blend.z);
                vertex_constructor.push_back(element.color_blend.w);
            }
        }

        //First we need to generate our VAO and VBO
        glGenVertexArrays(1, &vao_ID);
        glGenBuffers(1, &vbo_vertex_buffer_ID);

        //VAOs are used to store the associated vertex attribute pointers
        //Location 0 = vertex position
        //Location 1 = texture position
        //Location 2 = surface normal
        //Location 3 = texture index
        //Location 4 = material ambient
        //Location 5 = material diffuse
        //Location 6 = material specular
        //Location 7 = material reflective
        //Location 8 = color blend
        glBindVertexArray(vao_ID);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex_buffer_ID);

        unsigned int vertex_size = 23 * sizeof(float);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)(3*sizeof(float)));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(5*sizeof(float)));
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, vertex_size, (void*)(8*sizeof(float)));
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(9*sizeof(float)));
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(12*sizeof(float)));
        glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(15*sizeof(float)));
        glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, vertex_size, (void*)(18*sizeof(float)));
        glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, vertex_size, (void*)(19*sizeof(float)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        glEnableVertexAttribArray(7);
        glEnableVertexAttribArray(8);

        //Construct vertex VBO
        glBufferData(GL_ARRAY_BUFFER, vertex_constructor.size() * sizeof(float), &vertex_constructor[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    //Adds a prebuilt instance to the instance vector
    void AddInstance(Instance instance)
    {
        //Add instance to instance vector
        instance_vector.push_back(instance);
        instance_count++;
    }

    //Remove an instance from the instance vector by index
    void RemoveInstance(unsigned int index)
    {
        instance_vector.erase(instance_vector.begin() + index);
        instance_count--;
    }

    //Send data to the shaders and render every instance
    void Draw(Camera camera)
    {
        //Use our shader program
        program.Use();

        //Bind our VAO/VBOs
        glBindVertexArray(vao_ID);

        //Get matrices
        std::vector<glm::mat4> transform_matrix;
        for (int i = 0; i < instance_count; i++) transform_matrix.push_back(instance_vector[i].matrix);

        //Instance data

        /*
         * TODO: update this to use uniform buffers!!!
         */

        glm::mat4 view_matrix = camera.GetViewMatrix();
        glm::mat4 perspective_matrix = camera.GetPerspectiveMatrix();

        program.SetMat4("transform_matrix", instance_count, glm::value_ptr(transform_matrix[0]));
        program.SetMat4("camera_matrix", 1, glm::value_ptr(view_matrix));
        program.SetMat4("projection_matrix", 1, glm::value_ptr(perspective_matrix));

        //Lighting data
        //PointLight
        for (int i = 0; i < lighting_handler.point_lights.size(); i++)
        {
            //Get location as stinrg
            std::string point_light_position_str = ("point_lights[" + std::to_string(i) + "].position");
            std::string point_light_diffuse_str = ("point_lights[" + std::to_string(i) + "].diffuse");
            std::string point_light_specular_str = ("point_lights[" + std::to_string(i) + "].specular");

            std::string point_light_linear_str = ("point_lights[" + std::to_string(i) + "].linear");
            std::string point_light_quadratic_str = ("point_lights[" + std::to_string(i) + "].quadratic");

            //Convert location to char*
            char const *point_light_position_name = point_light_position_str.c_str();
            char const *point_light_diffuse_name = point_light_diffuse_str.c_str();
            char const *point_light_specular_name = point_light_specular_str.c_str();
            
            char const *point_light_linear_name = point_light_linear_str.c_str();
            char const *point_light_quadratic_name = point_light_quadratic_str.c_str();

            //Set light position
            program.SetVec3(point_light_position_name, 
                lighting_handler.point_lights[i].position.x,
                lighting_handler.point_lights[i].position.y,
                lighting_handler.point_lights[i].position.z);

            //Set light diffuse
            program.SetVec3(point_light_diffuse_name, 
                lighting_handler.point_lights[i].diffuse.x,
                lighting_handler.point_lights[i].diffuse.y,
                lighting_handler.point_lights[i].diffuse.z);

            //Set light specular
            program.SetVec3(point_light_specular_name, 
                lighting_handler.point_lights[i].specular.x,
                lighting_handler.point_lights[i].specular.y,
                lighting_handler.point_lights[i].specular.z);

            //Set light linear
            program.SetFloat(point_light_linear_name, 
                lighting_handler.point_lights[i].linear);

            //Set light quadratic
            program.SetFloat(point_light_quadratic_name, 
                lighting_handler.point_lights[i].quadratic);
        }

       //DirectionLight
        for (int i = 0; i < lighting_handler.direction_lights.size(); i++)
        {
            //Get location as stinrg
            std::string direction_light_position_str = ("direction_lights[" + std::to_string(i) + "].direction");
            std::string direction_light_diffuse_str = ("direction_lights[" + std::to_string(i) + "].diffuse");
            std::string direction_light_specular_str = ("direction_lights[" + std::to_string(i) + "].specular");

            //Convert location to char*
            char const *direction_light_position_name = direction_light_position_str.c_str();
            char const *direction_light_diffuse_name = direction_light_diffuse_str.c_str();
            char const *direction_light_specular_name = direction_light_specular_str.c_str();

            //Set light direction
            program.SetVec3(direction_light_position_name, 
                lighting_handler.direction_lights[i].direction.x,
                lighting_handler.direction_lights[i].direction.y,
                lighting_handler.direction_lights[i].direction.z);

            //Set light diffuse
            program.SetVec3(direction_light_diffuse_name, 
                lighting_handler.direction_lights[i].diffuse.x,
                lighting_handler.direction_lights[i].diffuse.y,
                lighting_handler.direction_lights[i].diffuse.z);

            //Set light specular
            program.SetVec3(direction_light_specular_name, 
                lighting_handler.direction_lights[i].specular.x,
                lighting_handler.direction_lights[i].specular.y,
                lighting_handler.direction_lights[i].specular.z);
        }

        //Global variables
        //Global ambient
        program.SetVec3("ambient", 
            lighting_handler.ambience.x,
            lighting_handler.ambience.y,
            lighting_handler.ambience.z);
        
        //Camera location
        program.SetVec3("camera_position",
            camera.camera_position.x,
            camera.camera_position.y,
            camera.camera_position.z);
        
        //Texture library
        for (int i = 0; i < texture_handler.texture_vector.size(); i++)
        {
            std::string texture_location_str = ("texture" + std::to_string(i+1));
            char const *texture_location_name = texture_location_str.c_str();
            program.SetInt(texture_location_name, i);
            texture_handler.texture_vector[i]->Bind(i);
        }

        //And finally, the draw call itself
        glDrawArraysInstanced(GL_TRIANGLES, 0, vertex_count, instance_count);
    }
};