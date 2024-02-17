#include "TransformableTextureShapeShader.h"

void TransformableTextureShapeShader::transferTraingles(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum)
{
    unsigned int numOfShapes = (vertices_sizeof / (singleVerticleDataElemsNum * 3 * sizeof(float)));
    setTrianglesNumber(numOfShapes);
    currentAttribElemSize = singleVerticleDataElemsNum;
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, singleVerticleElemsNum, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
};

