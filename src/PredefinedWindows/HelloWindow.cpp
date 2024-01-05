#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "HelloWindow.h"



void HelloWindow::renderLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        eventsProcessing();
        imageRendering();
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
}

void HelloWindow::setBackgroundColor(const float r, const float g, const float b)
{
    glClearColor(r,g,b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void HelloWindow::eventsProcessing()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void HelloWindow::imageRendering()
{
    setBackgroundColor(backgroundColor->r, backgroundColor->g, backgroundColor->b);
}
