#pragma once
#include "TextureIndicesShapeShaderDrawer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class TransformableTextureShapeShader: public TextureIndicesShapeShaderDrawer
{
private:
	glm::mat4 transformation;
	unsigned int transformLoc;

public:
	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor, unsigned int* textureIds, unsigned int texutresNumber, glm::mat4 *transformation) :
		TextureIndicesShapeShaderDrawer(vertexShaderPath, fragmentShaderPath, shapeFillColor, textureIds, texutresNumber),
		transformation(*transformation)
	{
		transformLoc = glGetUniformLocation(shaderProgramId, "transform");
	};
	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor, unsigned int* textureIds, unsigned int texutresNumber) :
		TextureIndicesShapeShaderDrawer(vertexShaderPath, fragmentShaderPath, shapeFillColor, textureIds, texutresNumber)
	{
		transformation = glm::mat4(1.0f);
		transformLoc = glGetUniformLocation(shaderProgramId, "transform");
	};
	virtual void drawShape(int shapeIdx)
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation));
		TextureIndicesShapeShaderDrawer::drawShape(shapeIdx);
	};
	virtual void drawAllShapes()
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation));
		TextureIndicesShapeShaderDrawer::drawAllShapes();
	};

	void setTransformation(glm::mat4* newTransformation) {
		transformation = *newTransformation;
	}
};