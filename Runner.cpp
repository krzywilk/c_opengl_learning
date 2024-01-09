#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "src/PredefinedWindows/HelloWindow.h"
#include <vector>
#include "src/utils/simples.cpp"
#include "src/ShapeDrawers/TrianglesShaderDrawer.h"

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
    TrianglesShaderDrawer singleTriangleDraw;
    float vertices[] = {
       -0.7f, -0.2f, 0.0f, // left  
        0.0f, -0.2f, 0.0f, // right 
        0.0f,  0.2f, 0.0f,  // top

        -1.0f, 0.7f, 0.0f, // 2_left  
        -0.7f, 0.7f, 0.0f, // 2_right 
        0.0f,  0.7f, 0.0f,  // 2_top

    };
    float color1[] = { 1.0f, 0.5f, 0.2f, 1.0f };

    TrianglesShaderDrawer singleTriangleDraw2;

    float vertices2[] = {
                -0.0f, -0.2f, 0.0f, // left  
        0.7f, -0.2f, 0.0f, // right 
        0.0f,  0.2f, 0.0f,  // top
    };
    float color2[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    singleTriangleDraw.transferData(vertices, sizeof(vertices)/sizeof(float));
    singleTriangleDraw2.transferData(vertices2, sizeof(vertices2) / sizeof(float));

    vector<ShaderDrawer*> triangleDrawers;
    triangleDrawers.push_back(&singleTriangleDraw);
    triangleDrawers.push_back(&singleTriangleDraw2);
    
    basicWindowTest.renderLoop(triangleDrawers);
    glfwTerminate();
}



