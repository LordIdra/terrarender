#pragma once

/*
 * A 2-dimensional texture that can be plastered onto a triangle
 * Loading and storing the texture is handled by the Texture2D struct
 * These should only be used by Triangle structs
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <external/image_config.cpp>


struct Texture2D
{
    //Used to reference the texture itself using OpenGL
    unsigned int ID;

    //Loads a texture file and creates a texture off that
    //The ID of the texture is stored for future use
    Texture2D() = default;

    Texture2D(const char *file_path, unsigned int input_format)
    {
        //Set to texture configuration port
        glActiveTexture(GL_TEXTURE0);

        //Flip the image the right way up
        stbi_set_flip_vertically_on_load(true); 

        //Load texture file
        int width, height, nrChannels;
        unsigned char *data = stbi_load(file_path, &width, &height, &nrChannels, 0);

        //Generate texture objects
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        //Generate textures + mipmaps
        glTexImage2D(
            GL_TEXTURE_2D,      //Bound texture to target
            0,                  //Mipmap level
            GL_RGB,             //Output format
            width,              //Width
            height,             //Height
            0,                  //Should always be 0 (deprecated)
            input_format,       //Input format
            GL_UNSIGNED_BYTE,   //Storage datatype
            data);              //Image itself

        //Generates all minimaps needed for currently bound texture
        glGenerateMipmap(GL_TEXTURE_2D);

        //Free memory which stored the image
        stbi_image_free(data);
    }

    //Deletes the texture from memory
    //Not as important as deleting VBOs/EBOs/VAOs since textures are more universal
    ~Texture2D()
    {
        glDeleteTextures(1, &ID);
    }

    //Bind a specific texture channel
    void Bind(unsigned int unit) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void Unbind(unsigned int unit) 
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //Sets how the texture is repeated across a triangle
    void SetWrapMode(unsigned int s_mode, unsigned int t_mode)
    {
        Bind(0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_mode);
        Unbind(0);
    }

    //Sets how the texture pixels blend together
    void SetFilterMode(unsigned int dimensions, unsigned int mimify_mode, unsigned int magnify_mode)
    {
        Bind(0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mimify_mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnify_mode);
        Unbind(0);
    }

    //Sets how different sizes of textures are calculated
    void SetMipmapMode(unsigned int dimensions, unsigned int mimify_mode, unsigned int magnify_mode)
    {
        Bind(0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mimify_mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnify_mode);
        Unbind(0);
    }
};