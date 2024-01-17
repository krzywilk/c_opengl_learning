#pragma once
#include "VertexColorIndicesShapeShaderDrawer.h"


void VertexColorIndicesShapeShaderDrawer::transferData(float vertices[], int vertices_sizeof)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexColorIndicesShapeShaderDrawer::transferData(float vertices[], int vertices_sizeof, unsigned int indices[], int indices_sizeof)
{
    setupIndices(indices, indices_sizeof);
    transferData(vertices, vertices_sizeof);
}

void VertexColorIndicesShapeShaderDrawer::setupIndices(unsigned int indices[], int indices_sizeof)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_sizeof, indices, GL_STATIC_DRAW);
    shapesNumber = indices_sizeof / (3 * sizeof(float));
}


void VertexColorIndicesShapeShaderDrawer::drawShape(int shapeIdx)
{
    glUseProgram(shaderProgramId);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * shapeIdx * sizeof(unsigned int)));
}

void VertexColorIndicesShapeShaderDrawer::drawAllShapes() {
    glUseProgram(shaderProgramId);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, shapesNumber * 3, GL_UNSIGNED_INT, 0);
}