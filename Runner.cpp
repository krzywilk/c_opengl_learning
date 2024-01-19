#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "src/PredefinedWindows/HelloWindow.h"
#include <vector>
#include "src/utils/simples.cpp"
#include "src/ShapeDrawers/StaticColor/StaticColorTrianglesShaderDrawer.h"
#include "src/ShapeDrawers/StaticColor/StaticColorIndicesShapeShaderDrawer.h"
#include "src/ShapeDrawers/DynamicColor/VertexColorIndicesShapeShaderDrawer.h"

namespace
{
    void init_GLFW(int glfw_version_major = 4, int glfw_version_minor = 4) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfw_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfw_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }
}

int main()
{
    init_GLFW();
    HelloWindow basicWindowTest = HelloWindow("Separate impl", 800, 600, rgb(0.3f, 0.1f, 0.1f));


    rgb color_topLeftRightTriangl(0.0f, 1.0f, 0.0f);
    float topLeftRightTriangle[] = {
       -0.7f, -0.2f, 0.0f, // left  
        0.0f, -0.2f, 0.0f, // right 
        0.0f,  0.2f, 0.0f,  // top

        -0.0f, -0.2f, 0.0f, // left  
        0.7f, -0.2f, 0.0f, // right 
        0.0f,  0.2f, 0.0f,  // top

    };

    rgb color_bottomRightTriangle(1.0f, 0.0f, 0.0f);
    float bottomRightTriangle[] = {
    -0.0f, -0.2f, 0.0f, // left  
    0.7f, -0.2f, 0.0f, // right 
    0.0f,  -0.6f, 0.0f,  // top
    };

    rgb color_rectangle_trainglesBased(0.0f, 0.0f, 1.0f);
    float rectangle_trainglesBased[] = {
     0.9f,  0.9f, 0.0f,  // top right
     0.9f, 0.5f, 0.0f,  // bottom right
     0.5f, 0.5f, 0.0f,  // bottom left
    0.5f,  0.9f, 0.0f   // top left 
    };
    float rectangle_dynamcColor_trainglesBased[] = {
     -0.5f,  0.9f, 0.0f,  1.0f, 0.0f, 0.0f, // top right
     -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
     -0.9f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // bottom left
    -0.9f,  0.9f, 0.0f ,  1.0f, 0.0f, 1.0f // top left 
    };

    unsigned int rectangle_trainglesBasedIndices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    rgb black(0.0f, 0.0f, 0.0f);



    StaticColorTrianglesShaderDrawer twoTrainglesDrawer("src/ShadersSourceCode/constant_color_shaders/vertex_shader.vs", "src/ShadersSourceCode/constant_color_shaders/fragment_shader.fs", & color_topLeftRightTriangl);
    StaticColorTrianglesShaderDrawer singleTriangleDrawer("src/ShadersSourceCode/constant_color_shaders/vertex_shader.vs", "src/ShadersSourceCode/constant_color_shaders/fragment_shader.fs", &color_bottomRightTriangle);
    StaticColorIndicesShapeShaderDrawer indicesRectangleDrawer("src/ShadersSourceCode/constant_color_shaders/vertex_shader.vs", "src/ShadersSourceCode/constant_color_shaders/fragment_shader.fs", &color_rectangle_trainglesBased);
    VertexColorIndicesShapeShaderDrawer indicesDynamicColorRectangleDrawer("src/ShadersSourceCode/dynamic_color_shaders/vertex_shader.vs", "src/ShadersSourceCode/dynamic_color_shaders/shift_color_fragment_shader.fs", &black);


    twoTrainglesDrawer.transferData(topLeftRightTriangle, sizeof(topLeftRightTriangle), 3,3);
    singleTriangleDrawer.transferData(bottomRightTriangle, sizeof(bottomRightTriangle), 3, 3);
    indicesRectangleDrawer.transferData(rectangle_trainglesBased, sizeof(rectangle_trainglesBased), 3,3, rectangle_trainglesBasedIndices, sizeof(rectangle_trainglesBasedIndices));
    indicesDynamicColorRectangleDrawer.transferDataWithColors(rectangle_dynamcColor_trainglesBased, sizeof(rectangle_dynamcColor_trainglesBased),3,3,6, rectangle_trainglesBasedIndices, sizeof(rectangle_trainglesBasedIndices));

    vector<ShaderDrawer*> triangleDrawers;
    triangleDrawers.push_back(&twoTrainglesDrawer);
    triangleDrawers.push_back(&singleTriangleDrawer);
    triangleDrawers.push_back(&indicesRectangleDrawer);
    triangleDrawers.push_back(&indicesDynamicColorRectangleDrawer);

    basicWindowTest.renderLoop(triangleDrawers);
    glfwTerminate();
}



