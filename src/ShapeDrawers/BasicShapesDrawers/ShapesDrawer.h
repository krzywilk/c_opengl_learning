#pragma once
#include "TrianglesDrawer.h"
class ShapesDrawer :
    public TrianglesDrawer
{

private:

    unsigned int EBO;
protected:
    void setupIndices(unsigned int* indices, int indices_sizeof);
public:
    ShapesDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) :
        TrianglesDrawer(vertexShaderPath, fragmentShaderPath,VAO,VBO),
        EBO(EBO)
    {
    };
    virtual void drawShape(int shapeIdx);
    virtual void drawAllShapes();

};

