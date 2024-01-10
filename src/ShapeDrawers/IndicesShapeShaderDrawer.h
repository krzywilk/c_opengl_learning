#pragma once
#include "ShaderDrawer.h"
class IndicesShapeShaderDrawer :
    public ShaderDrawer
{
private:
    unsigned int shapesNumber;
    unsigned int EBO;

public:
    IndicesShapeShaderDrawer():
        ShaderDrawer(),
        shapesNumber(0)
    {
        
        glGenBuffers(1, &EBO);
    };
    int getShapesNumber() const {
        return shapesNumber;
    };
    virtual void transferData(float vertices[], int vertices_sizeof);
    virtual void transferData(float vertices[], int vertices_sizeof, unsigned int indices[], int indices_sizeof);
    virtual void setupIndices(unsigned int indices[], int indices_sizeof);
    virtual void drawShape(int shapeIdx);
    virtual void drawAllShapes();

};

