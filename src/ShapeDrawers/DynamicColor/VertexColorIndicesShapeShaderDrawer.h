#pragma once
#include "../StaticColor/StaticColorIndicesShapeShaderDrawer.h"
class VertexColorIndicesShapeShaderDrawer :
    public StaticColorIndicesShapeShaderDrawer
{
private:
    unsigned int shapesNumber;
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

    void transferDataWithColors(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleDataElemsNum,unsigned int indices[], int indices_sizeof);


    virtual void transferData(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleDataElemsNum)
    {
        StaticColorIndicesShapeShaderDrawer::transferData(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum);
    };
    virtual void transferData(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleDataElemsNum, unsigned int indices[], int indices_sizeof)
    {
        StaticColorIndicesShapeShaderDrawer::transferData(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum, indices, indices_sizeof);
    };
    virtual void setupIndices(unsigned int indices[], int indices_sizeof)
    {
        StaticColorIndicesShapeShaderDrawer::setupIndices(indices, indices_sizeof);
    };
    virtual void drawShape(int shapeIdx)
    {
        StaticColorIndicesShapeShaderDrawer::drawShape(shapeIdx);
    };
    virtual void drawAllShapes() 
    {
        StaticColorIndicesShapeShaderDrawer::drawAllShapes();
    };
};

