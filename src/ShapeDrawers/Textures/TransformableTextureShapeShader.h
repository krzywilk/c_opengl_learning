#pragma once
#include "TexturedShapeDrawer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../BasicShapesDrawers/TransformableShapeShader.h"
#include <vector>


class TransformableTextureShapeShader: public TransformableShapeShader //TODO: not tested
{
private:
	unsigned int texutresNumber;
	std::vector<int> textureIds;
	std::map<int, std::string> id2ParamName;

public:
	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath,  unsigned int& VAO, unsigned int& VBO, unsigned int&  EBO,  glm::mat4 * modelTransformation, 
		glm::mat4* viewTransformation, glm::mat4* projectionTransformation, std::map<std::string, unsigned int> textureName2id) :
		TransformableShapeShader(vertexShaderPath, fragmentShaderPath, VAO, VBO,EBO, modelTransformation, viewTransformation, projectionTransformation)
	{

		texutresNumber = 0;
		std::map<std::string, unsigned int>::iterator iterator = textureName2id.begin();
		while (iterator != textureName2id.end())
		{
			texutresNumber += 1;
			std::string sVariableName = iterator->first;
			const char* pcVariable_name = sVariableName.c_str();
			const int textureId = iterator->second;
			//glUniform1i(glGetUniformLocation(shaderProgramId, pcVariable_name), textureId);
			textureIds.push_back(textureId);
			id2ParamName.insert({ textureId, sVariableName });
			iterator++;
		}
		
	};

	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, std::map<std::string, unsigned int> textureName2id) :
		TransformableShapeShader(vertexShaderPath, fragmentShaderPath, VAO, VBO, EBO)
	{
		texutresNumber = 0;
		std::map<std::string, unsigned int>::iterator iterator = textureName2id.begin();
		while (iterator != textureName2id.end())
		{
			texutresNumber += 1;
			std::string sVariableName = iterator->first;
			const char* pcVariable_name = sVariableName.c_str();
			const int textureId = iterator->second;
			//glUniform1i(glGetUniformLocation(shaderProgramId, pcVariable_name), textureId);
			textureIds.push_back(textureId);
			id2ParamName.insert({ textureId, sVariableName });
			iterator++;
		}
	}

	virtual void drawShape(int shapeIdx)
	{
		glUseProgram(shaderProgramId);
		for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
			setInt(id2ParamName[textureIds[textureIdx]], textureIdx);
			glActiveTexture(GL_TEXTURE0 + textureIdx);
			glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
		}

		TransformableShapeShader::drawShape(shapeIdx);
	};
	virtual void drawAllShapes()
	{
		glUseProgram(shaderProgramId);
		for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
			setInt(id2ParamName[textureIds[textureIdx]], textureIdx);
			glActiveTexture(GL_TEXTURE0 + textureIdx);
			glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
		}
		TransformableShapeShader::drawAllShapes();
	};

	virtual void drawAllTriangles()
	{
		glUseProgram(shaderProgramId);
		for (int textureIdx = 0; textureIdx < texutresNumber; textureIdx++) {
			setInt(id2ParamName[textureIds[textureIdx]], textureIdx);
			auto a = GL_TEXTURE0;
			auto b = GL_TEXTURE1;
			glActiveTexture(GL_TEXTURE0 + textureIdx);
			glBindTexture(GL_TEXTURE_2D, textureIds[textureIdx]);
		}
		TransformableShapeShader::drawAllTriangles();
	};
	void transferTraingles(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum);

};