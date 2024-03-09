#pragma once
#include "ShapesDrawer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class TransformableShapeShader : public ShapesDrawer
{
private:
	glm::mat4 modelTransformation;
	glm::mat4 viewTransformation;
	glm::mat4 projectionTransformation;
	unsigned int modelLoc;
	unsigned int viewLoc;
	unsigned int projectionLoc;

public:
	TransformableShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, glm::mat4* modelTransformation,
		glm::mat4* viewTransformation, glm::mat4* projectionTransformation) :
		ShapesDrawer(vertexShaderPath, fragmentShaderPath, VAO, VBO, EBO),
		modelTransformation(*modelTransformation),
		viewTransformation(*viewTransformation),
		projectionTransformation(*projectionTransformation)
	{
		modelLoc = glGetUniformLocation(shaderProgramId, "model");
		viewLoc = glGetUniformLocation(shaderProgramId, "view");
		projectionLoc = glGetUniformLocation(shaderProgramId, "projection");
	};

	TransformableShapeShader(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) :
		ShapesDrawer(vertexShaderPath, fragmentShaderPath, VAO, VBO, EBO)
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
		ShapesDrawer::drawShape(shapeIdx);
	};
	virtual void drawAllShapes()
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransformation));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionTransformation));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewTransformation));
		ShapesDrawer::drawAllShapes();
	};

	virtual void drawAllTriangles()
	{
		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransformation));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionTransformation));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewTransformation));
		ShapesDrawer::drawAllTriangles();
	};

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