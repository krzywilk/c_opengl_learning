#pragma once
#include "../ShaderDrawer.h"
class ColoredTrianglesDrawer :
    public ShaderDrawer
{
protected:
    rgb* shapeFillColor;

public:
    ColoredTrianglesDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor):
        ShaderDrawer(vertexShaderPath, fragmentShaderPath),
        shapeFillColor(shapeFillColor)
    {};
    int getTrianglesNumber() const {
        return trianglesNumber;
    };
    virtual void transferTriangles(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum);
    virtual void drawShape(int shapeIdx);
    virtual void drawAllTriangles() {
        ColoredTrianglesDrawer::drawAllShapes();
    }
    virtual void drawAllShapes();
    void setColor(rgb* shapeColor) {
        shapeFillColor = shapeColor;
    }
};

