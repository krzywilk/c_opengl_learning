#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "src/PredefinedWindows/HelloWindow.h"

void init_GLFW(int glfw_version_major = 4, int glfw_version_minor = 4) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfw_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfw_version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

int main()
{
    init_GLFW();
    HelloWindow basicWindowTest = HelloWindow("Separate impl", 800, 600, rgb(0.3f, 0.1f, 0.1f));
    basicWindowTest.renderLoop();
    glfwTerminate();
}



