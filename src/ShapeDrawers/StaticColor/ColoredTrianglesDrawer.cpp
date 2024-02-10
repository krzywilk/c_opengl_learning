#pragma once
#include "ColoredTrianglesDrawer.h"


void ColoredTrianglesDrawer::transferTriangles(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum)
{
    setTrianglesNumber(vertices_sizeof / (singleVerticleElemsNum * 3 * sizeof(float)));
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, singleVerticleElemsNum, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}


void ColoredTrianglesDrawer::drawShape(int shapeIdx)
{
    glUseProgram(shaderProgramId);
    glUniform4f(vertexColorLocation, shapeFillColor->r, shapeFillColor->g, shapeFillColor->b, 1.0f);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, shapeIdx * 3, 3);
}

void ColoredTrianglesDrawer::drawAllShapes() {
    glUseProgram(shaderProgramId);
    glUniform4f(vertexColorLocation, shapeFillColor->r, shapeFillColor->g, shapeFillColor->b, 1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, trianglesNumber * 3);
}