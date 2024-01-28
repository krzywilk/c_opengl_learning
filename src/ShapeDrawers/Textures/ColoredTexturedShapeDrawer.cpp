#include "ColoredTexturedShapeDrawer.h"

void ColoredTexturedShapeDrawer::transferVerticesIndicesTextureColors(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleColorSize, int singleVerticleTextureSize, int singleVerticleDataElemsNum, unsigned int* indices, int indices_sizeof)
{
	VertexColoredShapesDrawer::transferVerticesIndicesColors(vertices, vertices_sizeof, single_verticle_size, singleVerticleColorSize, singleVerticleDataElemsNum, indices, indices_sizeof);
	glVertexAttribPointer(2, singleVerticleTextureSize, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)((single_verticle_size + singleVerticleColorSize )* sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void ColoredTexturedShapeDrawer::transferVerticesIndicesTextures(float* vertices, int vertices_sizeof, int single_verticle_size, int singleVerticleTextureSize, int singleVerticleDataElemsNum, unsigned int* indices, int indices_sizeof)
{
	ColoredShapesDrawer::transferVerticesAndIndices(vertices, vertices_sizeof, single_verticle_size, singleVerticleDataElemsNum, indices, indices_sizeof);
	glVertexAttribPointer(2, singleVerticleTextureSize, GL_FLOAT, GL_FALSE, singleVerticleDataElemsNum * sizeof(float), (void*)(single_verticle_size * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
