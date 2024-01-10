#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "src/PredefinedWindows/HelloWindow.h"
#include <vector>
#include "src/utils/simples.cpp"
#include "src/ShapeDrawers/TrianglesShaderDrawer.h"
#include "src/ShapeDrawers/IndicesShapeShaderDrawer.h"

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



    float topLeftRightTriangle[] = {
       -0.7f, -0.2f, 0.0f, // left  
        0.0f, -0.2f, 0.0f, // right 
        0.0f,  0.2f, 0.0f,  // top

        -0.0f, -0.2f, 0.0f, // left  
        0.7f, -0.2f, 0.0f, // right 
        0.0f,  0.2f, 0.0f,  // top

    };

    float bottomRightTriangle[] = {
    -0.0f, -0.2f, 0.0f, // left  
    0.7f, -0.2f, 0.0f, // right 
    0.0f,  -0.6f, 0.0f,  // top
    };

    float rectangle_trainglesBased[] = {
     0.9f,  0.9f, 0.0f,  // top right
     0.9f, 0.5f, 0.0f,  // bottom right
     0.5f, 0.5f, 0.0f,  // bottom left
    0.5f,  0.9f, 0.0f   // top left 
    };
    unsigned int rectangle_trainglesBasedIndices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


    TrianglesShaderDrawer twoTrainglesDrawer;
    TrianglesShaderDrawer singleTriangleDrawer;
    IndicesShapeShaderDrawer indicesRectangleDrawer;

    twoTrainglesDrawer.transferData(topLeftRightTriangle, sizeof(topLeftRightTriangle));
    singleTriangleDrawer.transferData(bottomRightTriangle, sizeof(bottomRightTriangle));
    indicesRectangleDrawer.transferData(rectangle_trainglesBased, sizeof(rectangle_trainglesBased), rectangle_trainglesBasedIndices, sizeof(rectangle_trainglesBasedIndices));

    vector<ShaderDrawer*> triangleDrawers;
    triangleDrawers.push_back(&twoTrainglesDrawer);
    triangleDrawers.push_back(&singleTriangleDrawer);
    triangleDrawers.push_back(&indicesRectangleDrawer);

    basicWindowTest.renderLoop(triangleDrawers);
    glfwTerminate();
}



