#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "HelloWindow.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../ShapeDrawers/ShaderDrawer.h"
#include "../ShapeDrawers/Textures/TransformableTextureShapeShader.h"



void HelloWindow::drawOnlyRenderLoop(const vector<ShaderDrawer*>&trainglesToDraw)
{
    while (!glfwWindowShouldClose(window))
    {
        eventsProcessing();
        imageRendering();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        vector<ShaderDrawer*>::const_iterator  iterator_trainglesToDraw;
        for (iterator_trainglesToDraw = trainglesToDraw.begin(); iterator_trainglesToDraw != trainglesToDraw.end(); iterator_trainglesToDraw++)
        {
            (*iterator_trainglesToDraw)->drawAllTriangles();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
}

void HelloWindow::cameraRenderLoop(const vector<TransformableTextureShapeShader*>& trainglesToDraw)
{
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        eventsProcessing();
        imageRendering();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        vector<TransformableTextureShapeShader*>::const_iterator  iterator_trainglesToDraw;
        for (iterator_trainglesToDraw = trainglesToDraw.begin(); iterator_trainglesToDraw != trainglesToDraw.end(); iterator_trainglesToDraw++)
        {
            glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)width / (float)height, 0.1f, 100.0f);
            (*iterator_trainglesToDraw)->setProjectionTransformation(&projection);
            glm::mat4 view = camera->getViewMatrix();
            (*iterator_trainglesToDraw)->setViewTransformation(&view);
            (*iterator_trainglesToDraw)->drawAllTriangles();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void HelloWindow::setBackgroundColor(const float r, const float g, const float b)
{
    glClearColor(r,g,b, 1.0f);
}


void HelloWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto windowMasterClassPtr = static_cast<HelloWindow*>(glfwGetWindowUserPointer(window));
    windowMasterClassPtr->getCamera()->processMouseScroll(yoffset);
    
}
void HelloWindow::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    auto windowMasterClassPtr  = static_cast<HelloWindow*>(glfwGetWindowUserPointer(window));
    if (windowMasterClassPtr->getFirstMouse())
    {
        windowMasterClassPtr->setLastX(xpos);
        windowMasterClassPtr->setLastY(ypos);
        windowMasterClassPtr->setFirstMouse(false);
    }

    float xoffset = xpos - windowMasterClassPtr->getLastX();
    float yoffset = windowMasterClassPtr->getLastY() - ypos; // reversed since y-coordinates go from bottom to top

    windowMasterClassPtr->setLastX(xpos);
    windowMasterClassPtr->setLastY(ypos);

    windowMasterClassPtr->getCamera()->processMouseMovement(xoffset, yoffset);
}


void HelloWindow::eventsProcessing()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(RIGHT, deltaTime);
}

void HelloWindow::imageRendering()
{
    setBackgroundColor(backgroundColor.r, backgroundColor.g, backgroundColor.b);
}
