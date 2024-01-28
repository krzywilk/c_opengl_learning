#pragma once
#include "../DynamicColor/VertexColoredShapesDrawer.h"
#include <format>
#include <iostream>


class ColoredTexturedShapeDrawer : public VertexColoredShapesDrawer
{
protected:
    unsigned int texutresNumber;
    unsigned int* textureIds;
public:

    ColoredTexturedShapeDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor, unsigned int* textureIds, unsigned int texutresNumber) :
        VertexColoredShapesDrawer(vertexShaderPath, fragmentShaderPath, shapeFillColor),
        textureIds(textureIds),
        texutresNumber(texutresNumber)
    {
        glUseProgram(shaderProgramId);
        for (int i = 0; i < texutresNumber; i++) {
            std::string sVariableName = ("texture" + std::to_string(i));
            const char * pcVariable_name = sVariableName.c_str();
            glUniform1i(glGetUniformLocation(shaderProgramId, pcVariable_name), i);
        }

    };

	void transferVerticesIndicesTextureColors(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleTextureSize, int singleVerticleDataElemsNum, unsigned int* indices, int indices_sizeof);
	void transferVerticesIndicesTextures(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleTextureSize, int singleVerticleDataElemsNum, unsigned int* indices, int indices_sizeof);
    virtual void drawShape(int shapeIdx)
    {
        for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
            glActiveTexture(GL_TEXTURE0 + textureIdx);
            glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
        }

        VertexColoredShapesDrawer::drawShape(shapeIdx);
    };
    virtual void drawAllShapes()
    {
        for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
            glActiveTexture(GL_TEXTURE0 + textureIdx);
            glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx] );
        }
        VertexColoredShapesDrawer::drawAllShapes();
    };

    virtual void drawAllTrangles()
    {
        for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
            glActiveTexture(GL_TEXTURE0 + textureIdx);
            glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
        }
        VertexColoredShapesDrawer::drawAllTriangles();
    };
};

