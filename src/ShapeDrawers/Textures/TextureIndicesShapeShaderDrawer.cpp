#include "TextureIndicesShapeShaderDrawer.h"

void TextureIndicesShapeShaderDrawer::transferDataWithTexturesAndColors(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleTextureSize, int singleVerticleDataElemsNum, unsigned int indices[], int indices_sizeof)
{
	VertexColorIndicesShapeShaderDrawer::transferDataWithColors(vertices, vertices_sizeof, single_verticle_size, singleVerticleColorSize, singleVerticleDataElemsNum, indices, indices_sizeof);
	glVertexAttribPointer(2, singleVerticleTextureSize, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)((single_verticle_size + singleVerticleColorSize )* sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void TextureIndicesShapeShaderDrawer::transferDataWithTextures(float vertices[], int vertices_sizeof, int single_verticle_size, int singleVerticleTextureSize, int singleVerticleDataElemsNum, unsigned int indices[], int indices_sizeof)
{
	StaticColorIndicesShapeShaderDrawer::transferData(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum, indices, indices_sizeof);
	glVertexAttribPointer(2, singleVerticleTextureSize, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)(single_verticle_size * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
