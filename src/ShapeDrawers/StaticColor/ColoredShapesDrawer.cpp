#pragma once
#include "ColoredShapesDrawer.h"


void ColoredShapesDrawer::transferVerticesAndIndices(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleDataElemsNum, unsigned int* indices, int indices_sizeof)
{
    setupIndices(indices, indices_sizeof);
    transferTriangles(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum );
    setTrianglesNumber(indices_sizeof / (3 * sizeof(float)));
}

void ColoredShapesDrawer::setupIndices(unsigned int* indices, int indices_sizeof)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_sizeof, indices, GL_STATIC_DRAW);
}


void ColoredShapesDrawer::drawShape(int shapeIdx)
{
    glUseProgram(shaderProgramId);
    processCachedUniforms();
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * shapeIdx * sizeof(unsigned int)));
}

void ColoredShapesDrawer::drawAllShapes() {
    glUseProgram(shaderProgramId);
    processCachedUniforms();
    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, trianglesNumber * 3, GL_UNSIGNED_INT, 0);
}