#pragma once
#include "ColoredTrianglesDrawer.h"
class ColoredShapesDrawer :
    public ColoredTrianglesDrawer
{

private:

    unsigned int EBO;
protected:
    void setupIndices(unsigned int* indices, int indices_sizeof);
public:
    ColoredShapesDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO, rgb* shapeFillColor) :
        ColoredTrianglesDrawer(vertexShaderPath, fragmentShaderPath,VAO,VBO, shapeFillColor)
    {
        
        glGenBuffers(1, &EBO);
    };
    void transferVerticesAndIndices(float *vertices, int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum, unsigned int* indices, int indices_sizeof);
    virtual void drawShape(int shapeIdx);
    virtual void drawAllShapes();

};

