#include "TransformableTextureShapeShader.h"

void TransformableTextureShapeShader::transferTrianglesWithTextures(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleTextureSize, int singleVerticleDataElemsNum)
{
    TransformableTextureShapeShader::transferTraingles(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum);
    glVertexAttribPointer(1, singleVerticleTextureSize, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)(single_verticle_size * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TransformableTextureShapeShader::transferTraingles(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum)
{
    unsigned int numOfShapes = (vertices_sizeof / (singleVerticleDataElemsNum * 3 * sizeof(float)));
    setTrianglesNumber(numOfShapes);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, singleVerticleElemsNum, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
};

