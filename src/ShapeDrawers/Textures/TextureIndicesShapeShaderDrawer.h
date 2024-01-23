#pragma once
#include "../DynamicColor/VertexColorIndicesShapeShaderDrawer.h"
#include <format>
#include <iostream>


class TextureIndicesShapeShaderDrawer : public VertexColorIndicesShapeShaderDrawer
{
private:
    unsigned int *textureIds;
    unsigned int texutresNumber;

public:

    TextureIndicesShapeShaderDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor, unsigned int* textureIds, unsigned int texutresNumber) :
        VertexColorIndicesShapeShaderDrawer(vertexShaderPath, fragmentShaderPath, shapeFillColor),
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

	void transferDataWithTexturesAndColors(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleTextureSize, int singleVerticleDataElemsNum, unsigned int indices[], int indices_sizeof);
	void transferDataWithTextures(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleTextureSize, int singleVerticleDataElemsNum, unsigned int indices[], int indices_sizeof);
    virtual void drawShape(int shapeIdx)
    {
        for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
            glActiveTexture(GL_TEXTURE0 + textureIdx);
            glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
        }

        VertexColorIndicesShapeShaderDrawer::drawShape(shapeIdx);
    };
    virtual void drawAllShapes()
    {
        for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
            glActiveTexture(GL_TEXTURE0 + textureIdx);
            glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx] );
        }
        VertexColorIndicesShapeShaderDrawer::drawAllShapes();
    };
    void transferDataWithColors(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleDataElemsNum, unsigned int indices[], int indices_sizeof)
    {
        VertexColorIndicesShapeShaderDrawer::transferDataWithColors(vertices, vertices_sizeof, single_verticle_size, singleVerticleColorSize, singleVerticleDataElemsNum, indices, indices_sizeof);
    };

    virtual void transferData(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleDataElemsNum)
    {
        VertexColorIndicesShapeShaderDrawer::transferData(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum);
    };
    virtual void transferData(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleDataElemsNum, unsigned int indices[], int indices_sizeof)
    {
        VertexColorIndicesShapeShaderDrawer::transferData(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum, indices, indices_sizeof);
    };
    virtual void setupIndices(unsigned int indices[], int indices_sizeof)
    {
        VertexColorIndicesShapeShaderDrawer::setupIndices(indices, indices_sizeof);
    };
};

