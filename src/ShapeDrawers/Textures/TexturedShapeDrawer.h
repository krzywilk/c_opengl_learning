#pragma once
#include <format>
#include <iostream>
#include "../BasicShapesDrawers/ShapesDrawer.h"



class TexturedShapeDrawer : public ShapesDrawer
{
protected:
    unsigned int texutresNumber;
    unsigned int* textureIds; // pointer to array of ids
public:

    TexturedShapeDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int* textureIds, unsigned int texutresNumber) :
        ShapesDrawer(vertexShaderPath, fragmentShaderPath, VAO, VBO, EBO),
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
    virtual void drawShape(int shapeIdx)
    {
        for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
            glActiveTexture(GL_TEXTURE0 + textureIdx);
            glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
        }

        ShapesDrawer::drawShape(shapeIdx);
    };
    virtual void drawAllShapes()
    {
        for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
            glActiveTexture(GL_TEXTURE0 + textureIdx);
            glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx] );
        }
        ShapesDrawer::drawAllShapes();
    };

    virtual void drawAllTriangles()
    {
        for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
            glActiveTexture(GL_TEXTURE0 + textureIdx);
            glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
        }
        ShapesDrawer::drawAllTriangles();
    };
};

