#pragma once
#include "../ShaderDrawer.h"
class TrianglesDrawer :
    public ShaderDrawer
{

public:
    TrianglesDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO):
        ShaderDrawer(vertexShaderPath, fragmentShaderPath, VAO, VBO)
    {};
    int getTrianglesNumber() const {
        return trianglesNumber;
    };
    virtual void transferTriangles(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum);
    virtual void drawShape(int shapeIdx);
    virtual void drawAllTriangles() {
        TrianglesDrawer::drawAllShapes();
    }
    virtual void drawAllShapes();
};

