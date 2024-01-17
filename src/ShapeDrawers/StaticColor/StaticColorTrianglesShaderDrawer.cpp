#pragma once
#include "StaticColorTrianglesShaderDrawer.h"


void StaticColorTrianglesShaderDrawer::transferData(float vertices[], int vertices_sizeof)
{
    trianglesNumber = vertices_sizeof / (9 * sizeof(float));
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void StaticColorTrianglesShaderDrawer::drawShape(int shapeIdx)
{
    glUseProgram(shaderProgramId);
    glUniform4f(vertexColorLocation, shapeFillColor->r, shapeFillColor->g, shapeFillColor->b, 1.0f);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, shapeIdx * 3, 3);
}

void StaticColorTrianglesShaderDrawer::drawAllShapes() {
    glUseProgram(shaderProgramId);
    glUniform4f(vertexColorLocation, shapeFillColor->r, shapeFillColor->g, shapeFillColor->b, 1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, trianglesNumber * 3);
}