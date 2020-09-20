#pragma once

/*
 * Container that handles most things to do with a window
 */

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//'Raise' a generic error which outputs line, file, error and then pauses the 
//program until a key is pressed
#define raise_error(error)\
    std::cout << "=====[ERROR]=====" << "\n";\
    std::cout << "FILE: " << __FILE__ << "\n";\
    std::cout << "LINE: " << __LINE__ << "\n";\
    std::cout << error << "\n";\
    system("pause");


//Resizes window and scales rendering operations accordingly
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

struct Window
{
    //Stores the window itself
    GLFWwindow* window;

    //Time since last update
    float delta_time = 0.0f;

    //Cursor position
    double cursor_x = 0.0f;
    double cursor_y = 0.0f;

    //Cursor previous position
    double previous_cursor_x = 0.0f;
    double previous_cursor_y = 0.0f;

    //Initializer
    Window(
        unsigned int width, 
        unsigned int height, 
        const char* title, 
        unsigned int samples = 4,
        GLFWmonitor *monitor = NULL, 
        GLFWwindow *share = NULL)
    {
        //Create OpenGL window using provided parameters
        window = glfwCreateWindow(width, height, title, monitor, share);

        //Check window was successfully created
        if (window == NULL) 
        {
            raise_error("failed to create window"); 
            glfwTerminate();
        }

        //Set some window variables
        glfwWindowHint(GLFW_SAMPLES, samples);
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    //Schedule window to close
    void Close()
    {
        glfwSetWindowShouldClose(window, true);
    }

    //Find if window is scheduled to close
    int ShouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    //Clear the screen buffer
    void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    //Set the screen color
    void SetColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    //Enable/disable depth testing
    void SetDepthTesting(bool enabled)
    {
        if (enabled) glEnable(GL_DEPTH_TEST);
        else glEnable(GL_DEPTH_TEST);
    }

    //Swap back and front buffers
    void Update()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        delta_time = glfwGetTime() - delta_time;

        previous_cursor_x = cursor_x;
        previous_cursor_y = cursor_y;    

        glfwGetCursorPos(window, &cursor_x, &cursor_y);
    }

    //Check if a specific GL_KEY is pressed
    bool KeyPressed(unsigned int key)
    {
        if (glfwGetKey(window, key) == GLFW_PRESS) return true;
        else return false;
    }

    //Set the cursor's visibility
    void SetCursorState(bool status)
    {
        if (status) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
        else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    }
};