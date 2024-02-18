#pragma once
#include "TrianglesDrawer.h"


void TrianglesDrawer::transferTriangles(float *vertices, int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum)
{
    setTrianglesNumber(vertices_sizeof / (singleVerticleElemsNum * 3 * sizeof(float)));
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, vertices, GL_STATIC_DRAW);
    currentAttribElemSize = singleVerticleDataElemsNum;

}


void TrianglesDrawer::drawShape(int shapeIdx)
{
    glUseProgram(shaderProgramId);
    processCachedUniforms();
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, shapeIdx * 3, 3);
}

void TrianglesDrawer::drawAllShapes() {
    glUseProgram(shaderProgramId);
    processCachedUniforms();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, trianglesNumber * 3);
}