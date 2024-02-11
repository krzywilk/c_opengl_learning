#pragma once
#include "../StaticColor/ColoredShapesDrawer.h"
class VertexColoredShapesDrawer :
    public ColoredShapesDrawer
{

private:
    unsigned int EBO;

public:
    VertexColoredShapesDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO,unsigned int & EBO,  rgb* shapeFillColor) :
        ColoredShapesDrawer(vertexShaderPath, fragmentShaderPath, VAO, VBO, shapeFillColor),
        EBO(EBO)
    {
        
    };
    void transferVerticesIndicesColors(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleDataElemsNum,unsigned int* indices, int indices_sizeof);
};

