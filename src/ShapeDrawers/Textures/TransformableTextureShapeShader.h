#pragma once
#include "ColoredTexturedShapeDrawer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class TransformableTextureShapeShader: public ColoredTexturedShapeDrawer
{
private:
	glm::mat4 modelTransformation;
	glm::mat4 viewTransformation;
	glm::mat4 projectionTransformation;
	unsigned int modelLoc;
	unsigned int viewLoc;
	unsigned int projectionLoc;

public:
	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor, 
		unsigned int* textureIds, unsigned int texutresNumber, glm::mat4 * modelTransformation,
		glm::mat4* viewTransformation, glm::mat4* projectionTransformation) :
		ColoredTexturedShapeDrawer(vertexShaderPath, fragmentShaderPath, shapeFillColor, textureIds, texutresNumber),
		modelTransformation(*modelTransformation),
		viewTransformation(*viewTransformation),
		projectionTransformation(*projectionTransformation)
	{
		modelLoc = glGetUniformLocation(shaderProgramId, "model");
		viewLoc = glGetUniformLocation(shaderProgramId, "view");
		projectionLoc = glGetUniformLocation(shaderProgramId, "projection");
	};
	TransformableTextureShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, rgb* shapeFillColor, unsigned int* textureIds, unsigned int texutresNumber) :
		ColoredTexturedShapeDrawer(vertexShaderPath, fragmentShaderPath, shapeFillColor, textureIds, texutresNumber)
	{
		modelTransformation = glm::mat4(1.0f);
		viewTransformation = glm::mat4(1.0f);
		projectionTransformation = glm::mat4(1.0f);

		modelLoc = glGetUniformLocation(shaderProgramId, "model");
		viewLoc = glGetUniformLocation(shaderProgramId, "view");
		projectionLoc = glGetUniformLocation(shaderProgramId, "projection");
	};
	virtual void drawShape(int shapeIdx)
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransformation));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionTransformation));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewTransformation));
		ColoredTexturedShapeDrawer::drawShape(shapeIdx);
	};
	virtual void drawAllShapes()
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransformation));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionTransformation));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewTransformation));
		ColoredTexturedShapeDrawer::drawAllShapes();
	};

	virtual void drawAllTriangles()
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransformation));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionTransformation));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewTransformation));
		ColoredTexturedShapeDrawer::drawAllTriangles();
	};

	void transferTrianglesWithTextures(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleTextureSize, int singleVerticleDataElemsNum);

	void transferTraingles(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum);

	void setModelTransformation(glm::mat4* newModelTransformation) {
		modelTransformation = *newModelTransformation;
	};
	void setViewTransformation(glm::mat4* newViewTransformation) {
		viewTransformation = *newViewTransformation;
	};
	void setProjectionTransformation(glm::mat4* newProjectionTransformation) {
		projectionTransformation = *newProjectionTransformation;
	};
};