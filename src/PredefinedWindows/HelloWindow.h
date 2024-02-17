#pragma once
using namespace std;
#include <vector>
#include "../utils/simples.cpp"
#include "../ShapeDrawers/ShaderDrawer.h"
#include "../Cameras/CameraViewProcessing.h"
#include "../ShapeDrawers/Textures/TransformableTextureShapeShader.h"

class HelloWindow
{
private:
    unsigned int width;
    unsigned int height;

    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    const char windowName;
    rgb backgroundColor; 
    GLFWwindow* window; // TODO: to refactor? https://stackoverflow.com/questions/26246940/when-should-i-provide-a-destructor-for-my-class

    bool firstMouse;
    float lastX;
    float lastY;
    CameraViewProcessor* camera;


    void eventsProcessing();
    void imageRendering();

    void registerCallbacks() {
        glfwSetWindowUserPointer(window, this);

        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
    };

public:
    HelloWindow(CameraViewProcessor* camera, const char* windowName = "basic_window", unsigned int width = 800, unsigned int height = 600, rgb backgroundColor = rgb(0,0,0)) :
        windowName(*windowName),
        camera(camera),
        width(width),
        height(height),
        backgroundColor(backgroundColor),
        firstMouse(true),
        lastX(400),
        lastY(300)
    {
        GLFWwindow* window = glfwCreateWindow(width, height, windowName, NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });
        this->window = window;
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
        registerCallbacks();
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    };
    void drawOnlyRenderLoop(const vector<ShaderDrawer*>& trainglesToDraw);
    void cameraRenderLoop(const vector<TransformableTextureShapeShader*>& trainglesToDraw);
    void setBackgroundColor(const float r, const float g, const float b);
    void static scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void static mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    unsigned int getWidth() {
        return width;
    };
    unsigned int getHeight() {
        return height;
    };
    void setFirstMouse(bool firstMouse) {
        this->firstMouse = firstMouse;
    }
    void setLastX(float lastX)
    {
        this->lastX = lastX;
    }
    void setLastY(float lastY)
    {
        this->lastY = lastY;
    }
    bool getFirstMouse() {
        return firstMouse;
    }
    float getLastX()
    {
        return lastX;
    }
    float getLastY()
    {
        return lastY;
    }
    CameraViewProcessor* getCamera() {
        return camera;
    }
};


