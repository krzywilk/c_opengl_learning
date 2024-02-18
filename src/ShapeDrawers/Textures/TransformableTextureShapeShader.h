#pragma once
#include "TexturedShapeDrawer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../BasicShapesDrawers/TransformableShapeShader.h"


class TransformableTextureShapeShader: public TransformableShapeShader //TODO: not tested
{
private:
	unsigned int texutresNumber;
	unsigned int* textureIds; // pointer to array of ids

public:
	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, 
		unsigned int* textureIds, unsigned int texutresNumber, unsigned int& VAO, unsigned int& VBO, unsigned int&  EBO,  glm::mat4 * modelTransformation,
		glm::mat4* viewTransformation, glm::mat4* projectionTransformation) :
		TransformableShapeShader(vertexShaderPath, fragmentShaderPath, VAO, VBO,EBO, modelTransformation, viewTransformation, projectionTransformation),
		textureIds(textureIds),
		texutresNumber(texutresNumber)
	{

		for (int i = 0; i < texutresNumber; i++) {
			std::string sVariableName = ("texture" + std::to_string(i));
			const char* pcVariable_name = sVariableName.c_str();
			glUniform1i(glGetUniformLocation(shaderProgramId, pcVariable_name), i);
		}
	};

	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int* textureIds, unsigned int texutresNumber) :
		TransformableShapeShader(vertexShaderPath, fragmentShaderPath, VAO, VBO, EBO),
		textureIds(textureIds),
		texutresNumber(texutresNumber)
	{

		for (int i = 0; i < texutresNumber; i++) {
			std::string sVariableName = ("texture" + std::to_string(i));
			const char* pcVariable_name = sVariableName.c_str();
			glUniform1i(glGetUniformLocation(shaderProgramId, pcVariable_name), i);
		}
	};
	virtual void drawShape(int shapeIdx)
	{
		glUseProgram(shaderProgramId);
		for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
			glActiveTexture(GL_TEXTURE0 + textureIdx);
			glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
		}

		TransformableShapeShader::drawShape(shapeIdx);
	};
	virtual void drawAllShapes()
	{
		glUseProgram(shaderProgramId);
		for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
			glActiveTexture(GL_TEXTURE0 + textureIdx);
			glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
		}
		TransformableShapeShader::drawAllShapes();
	};

	virtual void drawAllTriangles()
	{
		glUseProgram(shaderProgramId);
		for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
			glActiveTexture(GL_TEXTURE0 + textureIdx);
			glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
		}
		TransformableShapeShader::drawAllTriangles();
	};
	void transferTraingles(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum);

};