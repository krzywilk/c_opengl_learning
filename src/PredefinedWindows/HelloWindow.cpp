#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "HelloWindow.h"

#include <vector>
#include "../ShapeDrawers/ShaderDrawer.h"



void HelloWindow::renderLoop(const vector<ShaderDrawer*>&trainglesToDraw)
{
    while (!glfwWindowShouldClose(window))
    {
        eventsProcessing();
        imageRendering();
        vector<ShaderDrawer*>::const_iterator  iterator_trainglesToDraw;
        for (iterator_trainglesToDraw = trainglesToDraw.begin(); iterator_trainglesToDraw != trainglesToDraw.end(); iterator_trainglesToDraw++)
            (*iterator_trainglesToDraw)->drawAllShapes();
      
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
