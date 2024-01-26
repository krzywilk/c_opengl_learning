#pragma once
#include "../StaticColor/StaticColorIndicesShapeShaderDrawer.h"
class VertexColorIndicesShapeShaderDrawer :
    public StaticColorIndicesShapeShaderDrawer
{
protected:
    unsigned int shapesNumber;
private:
    
    unsigned int EBO;

public:
    VertexColorIndicesShapeShaderDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor) :
        StaticColorIndicesShapeShaderDrawer(vertexShaderPath, fragmentShaderPath, shapeFillColor),
        shapesNumber(0)
    {
        glGenBuffers(1, &EBO);
    };
    int getShapesNumber() const {
        return shapesNumber;
    };

    void transferDataWithColors(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleDataElemsNum,unsigned int* indices, int indices_sizeof);
};

