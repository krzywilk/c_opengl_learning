#pragma once
#include "ShaderDrawer.h"
class TrianglesShaderDrawer :
    public ShaderDrawer
{
private:
    unsigned int trianglesNumber;

public:
    TrianglesShaderDrawer():
        ShaderDrawer(),
        trianglesNumber(0) 
    {};
    int getTrianglesNumber() const {
        return trianglesNumber;
    };
    virtual void transferData(float vertices[], int vertices_length);
    virtual void drawShape(int shapeIdx);
    virtual void drawAllShapes();

};

