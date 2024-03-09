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
#include "src/ShapeDrawers/BasicShapesDrawers/TransformableShapeShader.h"


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

    void setLightValues(TransformableTextureShapeShader* lightingShader,CameraViewProcessor* camera, glm::vec3* pointLightPositions) {
        // directional light
        lightingShader->setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f), true);
        lightingShader->setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f), true);
        lightingShader->setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f), true);
        lightingShader->setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f), true);
        // point light 1
        lightingShader->setVec3("pointLights[0].position", pointLightPositions[0], true);
        lightingShader->setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f), true);
        lightingShader->setVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f), true);
        lightingShader->setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f), true);
        lightingShader->setFloat("pointLights[0].constant", 1.0f, true);
        lightingShader->setFloat("pointLights[0].linear", 0.09f, true);
        lightingShader->setFloat("pointLights[0].quadratic", 0.032f, true);
        // point light 2
        lightingShader->setVec3("pointLights[1].position", pointLightPositions[1], true);
        lightingShader->setVec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f), true);
        lightingShader->setVec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f), true);
        lightingShader->setVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f), true);
        lightingShader->setFloat("pointLights[1].constant", 1.0f, true);
        lightingShader->setFloat("pointLights[1].linear", 0.09f, true);
        lightingShader->setFloat("pointLights[1].quadratic", 0.032f, true);
        // point light 3
        lightingShader->setVec3("pointLights[2].position", pointLightPositions[2], true);
        lightingShader->setVec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f), true);
        lightingShader->setVec3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f), true);
        lightingShader->setVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f), true);
        lightingShader->setFloat("pointLights[2].constant", 1.0f, true);
        lightingShader->setFloat("pointLights[2].linear", 0.09f, true);
        lightingShader->setFloat("pointLights[2].quadratic", 0.032f, true);
        // point light 4
        lightingShader->setVec3("pointLights[3].position", pointLightPositions[3], true);
        lightingShader->setVec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f), true);
        lightingShader->setVec3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f), true);
        lightingShader->setVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f), true);
        lightingShader->setFloat("pointLights[3].constant", 1.0f, true);
        lightingShader->setFloat("pointLights[3].linear", 0.09f, true);
        lightingShader->setFloat("pointLights[3].quadratic", 0.032f, true);
        // spotLight
        lightingShader->setVec3_pointerValue("spotLight.position", camera->getPosition(), true);
        lightingShader->setVec3_pointerValue("spotLight.direction", camera->getFront(), true);
        lightingShader->setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f), true);
        lightingShader->setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f), true);
        lightingShader->setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f), true);
        lightingShader->setFloat("spotLight.constant", 1.0f, true);
        lightingShader->setFloat("spotLight.linear", 0.09f, true);
        lightingShader->setFloat("spotLight.quadratic", 0.032f, true);
        lightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)), true);
        lightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)), true);
    }
}

static int main3d() {
    init_GLFW();
    CameraViewProcessor camera = CameraViewProcessor(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    HelloWindow basicWindowTest = HelloWindow(&camera, "Separate impl", 800, 600, rgb(0.f, 0.f, 0.f));
    TexturesDirLoader simpleTextureLoader("static_files/textures/container", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    simpleTextureLoader.loadTextures();

    rgb black(0.0f, 0.0f, 0.0f);
    rgb white(1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO = -1;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);


    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);


    TransformableShapeShader lightSourceDrawer("src/ShadersSourceCode/constant_color_shaders/transformation_vertex_shader.vs", "src/ShadersSourceCode/constant_color_shaders/fragment_shader.fs", lightCubeVAO, VBO, EBO);
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    glm::vec3 secBox(1.2f, 3.0f, 2.0f);

    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 diffuseColor = glm::vec3(lightColor) * glm::vec3(0.5f); // decrease the influence
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
    lightSourceDrawer.setVec4("color", lightColor, true);

    glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
    };

    TransformableTextureShapeShader texturerRectangleDrawer("src/ShadersSourceCode/light_shaders/multiple_lights_maps_vertex_shader.vs", "src/ShadersSourceCode/light_shaders/multiple_lights_maps_fragment_shader.fs", VAO, VBO, EBO, simpleTextureLoader.getName2id());
    TransformableTextureShapeShader texturerRectangleDrawer_small("src/ShadersSourceCode/light_shaders/multiple_lights_maps_vertex_shader.vs", "src/ShadersSourceCode/light_shaders/multiple_lights_maps_fragment_shader.fs", VAO, VBO, EBO, simpleTextureLoader.getName2id());

    texturerRectangleDrawer.setVec3_pointerValue("viewPos", camera.getPosition(), true);

    texturerRectangleDrawer.setFloat("material.shininess", 32, true);
    texturerRectangleDrawer.setInt("material.diffuse", 0, true);
    texturerRectangleDrawer.setInt("material.specular", 1, true);

    texturerRectangleDrawer.setVec3("light.position", lightPos, true);
    texturerRectangleDrawer.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f), true);
    texturerRectangleDrawer.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f), true);
    texturerRectangleDrawer.setVec3("light.specular", glm::vec3(1.0), true);
    setLightValues(&texturerRectangleDrawer, &camera, pointLightPositions);

//small_box
    texturerRectangleDrawer_small.setVec3_pointerValue("viewPos", camera.getPosition(), true);

    texturerRectangleDrawer_small.setFloat("material.shininess", 32, true);
    texturerRectangleDrawer.setInt("material.diffuse", 0, true);
    texturerRectangleDrawer.setInt("material.specular", 1, true);

    texturerRectangleDrawer_small.setVec3("light.position", lightPos, true);
    texturerRectangleDrawer_small.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f), true);
    texturerRectangleDrawer_small.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f), true);
    texturerRectangleDrawer_small.setVec3("light.specular", glm::vec3(1.0), true);
    setLightValues(&texturerRectangleDrawer_small, &camera, pointLightPositions);


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    model = glm::translate(model, secBox);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    texturerRectangleDrawer_small.setModelTransformation(&model);



    model = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightSourceDrawer.setModelTransformation(&model);
    texturerRectangleDrawer.transferTriangles(vertices, sizeof(vertices), 3, 8);
    texturerRectangleDrawer.setVertexAttribPointer(0, 3, 0);
    texturerRectangleDrawer.setVertexAttribPointer(1, 3, 3);
    texturerRectangleDrawer.setVertexAttribPointer(2, 2, 6);

    texturerRectangleDrawer_small.setCurrentAttribElemSize(texturerRectangleDrawer.getCurrentAttribElemSize());
    texturerRectangleDrawer_small.setTrianglesNumber(texturerRectangleDrawer.getTrianglesNumber());
    texturerRectangleDrawer_small.setVertexAttribPointer(0, 3, 0);
    texturerRectangleDrawer_small.setVertexAttribPointer(1, 3, 3);
    texturerRectangleDrawer_small.setVertexAttribPointer(2, 2, 6);

    lightSourceDrawer.setCurrentAttribElemSize(texturerRectangleDrawer.getCurrentAttribElemSize());
    lightSourceDrawer.setTrianglesNumber(texturerRectangleDrawer.getTrianglesNumber());

    lightSourceDrawer.setVertexAttribPointer(0, 3, 0);



    vector<TransformableShapeShader*> triangleDrawers;
    triangleDrawers.push_back(&texturerRectangleDrawer);
    triangleDrawers.push_back(&lightSourceDrawer);
    triangleDrawers.push_back(&texturerRectangleDrawer_small);

    basicWindowTest.cameraRenderLoop(triangleDrawers);
    glfwTerminate();
    return 0;
}
int main() {
    return main3d();
}


