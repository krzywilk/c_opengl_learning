#pragma once
using namespace std;
#include <vector>
#include "../utils/simples.cpp"
#include "../ShapeDrawers/ShaderDrawer.h"


class HelloWindow
{
private:
    unsigned int width;
    unsigned int height;

    const char* windowName;
    rgb* backgroundColor;
    GLFWwindow* window;

    void eventsProcessing();
    void imageRendering();


public:
    HelloWindow(const char* windowName = "basic_window", unsigned int width = 800, unsigned int height = 600, rgb backgroundColor = rgb(0,0,0)) :
        windowName(windowName),
        width(width),
        height(height),
        backgroundColor(&backgroundColor)
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
        
    };
    void renderLoop(const vector<ShaderDrawer*>& trainglesToDraw);
    void setBackgroundColor(const float r, const float g, const float b);
    unsigned int getWidth() {
        return width;
    };
    unsigned int getHeight() {
        return height;
    };
};


