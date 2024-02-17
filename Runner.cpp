#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "src/PredefinedWindows/HelloWindow.h"
#include <vector>
#include "src/utils/simples.cpp"
#include "src/ShapeDrawers/BasicShapesDrawers/TrianglesDrawer.h"
#include "src/ShapeDrawers/BasicShapesDrawers/ShapesDrawer.h"
#include "src/Textures/Loaders/TexturesDirLoader.h"
#include "src/ShapeDrawers/Textures/TexturedShapeDrawer.h"
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
    lightSourceDrawer.transferTraingles(vertices, sizeof(vertices), 3, 5);
    texturerRectangleDrawer.setVertexAttribPointer(2, 2, 3);

    vector<TransformableTextureShapeShader*> triangleDrawers;
    triangleDrawers.push_back(&texturerRectangleDrawer);
    triangleDrawers.push_back(&lightSourceDrawer);

    basicWindowTest.cameraRenderLoop(triangleDrawers);
    glfwTerminate();
    return 0;
}
int main() {
    return main3d();
}


