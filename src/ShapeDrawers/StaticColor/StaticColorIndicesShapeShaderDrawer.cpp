#pragma once
#include "StaticColorIndicesShapeShaderDrawer.h"


void StaticColorIndicesShapeShaderDrawer::transferData(float *vertices, int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, singleVerticleElemsNum, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void StaticColorIndicesShapeShaderDrawer::transferData(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleDataElemsNum, unsigned int* indices, int indices_sizeof)
{
    setupIndices(indices, indices_sizeof);
    transferData(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum );
}

void StaticColorIndicesShapeShaderDrawer::setupIndices(unsigned int* indices, int indices_sizeof)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_sizeof, indices, GL_STATIC_DRAW);
    shapesNumber = indices_sizeof / (3 * sizeof(float));
}


void StaticColorIndicesShapeShaderDrawer::drawShape(int shapeIdx)
{
    glUseProgram(shaderProgramId);
    glUniform4f(vertexColorLocation, shapeFillColor->r, shapeFillColor->g, shapeFillColor->b, 1.0f);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * shapeIdx * sizeof(unsigned int)));
}

void StaticColorIndicesShapeShaderDrawer::drawAllShapes() {
    glUseProgram(shaderProgramId);
    glUniform4f(vertexColorLocation, shapeFillColor->r, shapeFillColor->g, shapeFillColor->b, 1.0f);
    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, shapesNumber * 3, GL_UNSIGNED_INT, 0);
}