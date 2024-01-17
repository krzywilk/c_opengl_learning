#pragma once
#include "../ShaderDrawer.h"
class StaticColorTrianglesShaderDrawer :
    public ShaderDrawer
{
private:
    unsigned int trianglesNumber;
    rgb* shapeFillColor;

public:
    StaticColorTrianglesShaderDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor):
        ShaderDrawer(vertexShaderPath, fragmentShaderPath),
        shapeFillColor(shapeFillColor),
        trianglesNumber(0) 
    {};
    int getTrianglesNumber() const {
        return trianglesNumber;
    };
    virtual void transferData(float vertices[], int vertices_sizeof);
    virtual void drawShape(int shapeIdx);
    virtual void drawAllShapes();
    void setColor(rgb* shapeColor) {
        shapeFillColor = shapeColor;
    }
};

