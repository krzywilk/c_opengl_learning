#pragma once
#include "../StaticColor/ColoredShapesDrawer.h"
class VertexColoredShapesDrawer :
    public ColoredShapesDrawer
{

private:
    unsigned int EBO;

public:
    VertexColoredShapesDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor) :
        ColoredShapesDrawer(vertexShaderPath, fragmentShaderPath, shapeFillColor)
    {
        glGenBuffers(1, &EBO);
    };
    void transferVerticesIndicesColors(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleDataElemsNum,unsigned int* indices, int indices_sizeof);
};

