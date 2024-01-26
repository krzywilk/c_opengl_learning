#pragma once
#include "../ShaderDrawer.h"
class StaticColorIndicesShapeShaderDrawer :
    public ShaderDrawer
{
private:
    unsigned int shapesNumber;
    unsigned int EBO;
    rgb* shapeFillColor;

public:
    StaticColorIndicesShapeShaderDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor) :
        ShaderDrawer(vertexShaderPath, fragmentShaderPath),
        shapeFillColor(shapeFillColor),
        shapesNumber(0)
    {
        
        glGenBuffers(1, &EBO);
    };
    int getShapesNumber() const {
        return shapesNumber;
    };
    virtual void transferData(float *vertices, int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum);
    virtual void transferData(float *vertices, int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum, unsigned int* indices, int indices_sizeof);
    virtual void setupIndices(unsigned int *indices, int indices_sizeof);
    virtual void drawShape(int shapeIdx);
    virtual void drawAllShapes();
    void setColor(rgb* shapeColor) {
        shapeFillColor = shapeColor;
    }
};

