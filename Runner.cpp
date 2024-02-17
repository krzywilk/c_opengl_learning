#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "src/PredefinedWindows/HelloWindow.h"
#include <vector>
#include "src/utils/simples.cpp"
#include "src/ShapeDrawers/StaticColor/ColoredTrianglesDrawer.h"
#include "src/ShapeDrawers/StaticColor/ColoredShapesDrawer.h"
#include "src/ShapeDrawers/DynamicColor/VertexColoredShapesDrawer.h"
#include "src/Textures/Loaders/TexturesDirLoader.h"
#include "src/ShapeDrawers/Textures/ColoredTexturedShapeDrawer.h"
#include<array> 
#include "src/ShapeDrawers/Textures/TransformableTextureShapeShader.h"


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

static int main3d() {
    init_GLFW();
    CameraViewProcessor camera = CameraViewProcessor(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    HelloWindow basicWindowTest = HelloWindow(&camera, "Separate impl", 800, 600, rgb(0.3f, 0.1f, 0.1f));
    TexturesDirLoader simpleTextureLoader("static_files/textures/", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    simpleTextureLoader.loadTextures();
    string texture2load[] = { "container.jpg", "awesomeface.png" };
    unsigned int textureIds[2];
    unsigned int current_idx = 0;
    for (string name : texture2load) {
        textureIds[current_idx] = simpleTextureLoader.getTextureId(&name);
        current_idx++;
    }
    rgb black(0.0f, 0.0f, 0.0f);
    rgb white(1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    float vertices[] = {
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

           -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO = -1;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);


    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    TransformableTextureShapeShader texturerRectangleDrawer("src/ShadersSourceCode/constant_color_shaders/transformation_vertex_shader.vs", "src/ShadersSourceCode/constant_color_shaders/textures_color_shift_fragment_shader.fs", VAO, VBO, EBO, textureIds, current_idx);
    texturerRectangleDrawer.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f,0.0f), true);
    
    TransformableTextureShapeShader lightSourceDrawer("src/ShadersSourceCode/light_shaders/light_vertex_shader.vs", "src/ShadersSourceCode/light_shaders/light_fragment_shader.fs", lightCubeVAO, VBO, EBO,  textureIds, current_idx);
    lightSourceDrawer.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f), true);
    lightSourceDrawer.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f), true);

    
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightSourceDrawer.setModelTransformation(&model);
    texturerRectangleDrawer.transferTraingles(vertices, sizeof(vertices), 3, 5);
    texturerRectangleDrawer.setVertexAttribPointer(2, 2, 3);
    lightSourceDrawer.transferTraingles(vertices, sizeof(vertices), 3, 5);

    vector<TransformableTextureShapeShader*> triangleDrawers;
    triangleDrawers.push_back(&texturerRectangleDrawer);
    triangleDrawers.push_back(&lightSourceDrawer);

    basicWindowTest.cameraRenderLoop(triangleDrawers);
    glfwTerminate();
    return 0;
}
/*
static int main2d()
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

    float rectangle_textures_dynamcColor_trainglesBased[] = {
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int rectangle_trainglesBasedIndices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    rgb black(0.0f, 0.0f, 0.0f);

    TexturesDirLoader simpleTextureLoader("static_files/textures/", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    simpleTextureLoader.loadTextures();
    string texture2load[] = {  "container.jpg", "awesomeface.png"};
    unsigned int textureIds[2];
    unsigned int current_idx = 0;
    for (string name: texture2load) {
        textureIds[current_idx] = simpleTextureLoader.getTextureId(&name);
        current_idx++;
    }
    

    ColoredTrianglesDrawer twoTrainglesDrawer("src/ShadersSourceCode/constant_color_shaders/vertex_shader.vs", "src/ShadersSourceCode/constant_color_shaders/fragment_shader.fs", & color_topLeftRightTriangl);
    ColoredTrianglesDrawer singleTriangleDrawer("src/ShadersSourceCode/constant_color_shaders/vertex_shader.vs", "src/ShadersSourceCode/constant_color_shaders/fragment_shader.fs", &color_bottomRightTriangle);
    ColoredShapesDrawer indicesRectangleDrawer("src/ShadersSourceCode/constant_color_shaders/vertex_shader.vs", "src/ShadersSourceCode/constant_color_shaders/fragment_shader.fs", &color_rectangle_trainglesBased);
    VertexColoredShapesDrawer indicesDynamicColorRectangleDrawer("src/ShadersSourceCode/dynamic_color_shaders/vertex_shader.vs", "src/ShadersSourceCode/dynamic_color_shaders/shift_color_fragment_shader.fs", &black);
    
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    TransformableTextureShapeShader texturerRectangleDrawer("src/ShadersSourceCode/dynamic_color_shaders/transformation_vertex_shader.vs", "src/ShadersSourceCode/dynamic_color_shaders/shift_color_textures_fragment_shader.fs", &black, textureIds, current_idx);
    texturerRectangleDrawer.setModelTransformation(&trans);

    twoTrainglesDrawer.transferTriangles(topLeftRightTriangle, sizeof(topLeftRightTriangle), 3,3);
    singleTriangleDrawer.transferTriangles(bottomRightTriangle, sizeof(bottomRightTriangle), 3, 3);
    indicesRectangleDrawer.transferVerticesAndIndices(rectangle_trainglesBased, sizeof(rectangle_trainglesBased), 3,3, rectangle_trainglesBasedIndices, sizeof(rectangle_trainglesBasedIndices));
    indicesDynamicColorRectangleDrawer.transferVerticesIndicesColors(rectangle_dynamcColor_trainglesBased, sizeof(rectangle_dynamcColor_trainglesBased),3,3,6, rectangle_trainglesBasedIndices, sizeof(rectangle_trainglesBasedIndices));
    texturerRectangleDrawer.transferVerticesIndicesTextureColors(rectangle_textures_dynamcColor_trainglesBased, sizeof(rectangle_textures_dynamcColor_trainglesBased),3,3,2,8, rectangle_trainglesBasedIndices, sizeof(rectangle_trainglesBasedIndices));

    vector<ShaderDrawer*> triangleDrawers;
    triangleDrawers.push_back(&twoTrainglesDrawer);
    triangleDrawers.push_back(&singleTriangleDrawer);
    triangleDrawers.push_back(&indicesRectangleDrawer);
    triangleDrawers.push_back(&indicesDynamicColorRectangleDrawer);
    triangleDrawers.push_back(&texturerRectangleDrawer);

    basicWindowTest.drawOnlyRenderLoop(triangleDrawers);
    glfwTerminate();
    return  0;
}
*/
int main() {
    return main3d();
}


