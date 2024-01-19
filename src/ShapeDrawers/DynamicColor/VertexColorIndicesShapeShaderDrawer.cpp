#pragma once
#include "VertexColorIndicesShapeShaderDrawer.h"




void VertexColorIndicesShapeShaderDrawer::transferDataWithColors(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleDataElemsNum, unsigned int indices[], int indices_sizeof)
{

    StaticColorIndicesShapeShaderDrawer::transferData(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum,  indices, indices_sizeof);
    glVertexAttribPointer(1, singleVerticleColorSize, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)( single_verticle_size* sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
