#include <iostream>
#include "chunk.hpp"
#include "terraingeneration.hpp"
#include "geodegeneration.hpp"

Chunk::Chunk(Coord c, int s, double sp, int se)
{
	coordinates = c;
	size = s;
	space = sp;
	seed = se;

	// Create terrain
	//GenerateTerrain(c.x, c.y, s, (float)space, terrainVertices, terrainIndices);
	GenerateGeode(50,5,terrainVertices, terrainIndices);

	terrain = new Object(terrainVertices, terrainIndices, GL_TRIANGLES);
	terrain->SetModelMatrix(glm::translate(	glm::mat4(),
								glm::vec3((float)(coordinates.x * space * size),
								0.0f,
								(float)(coordinates.y * space * size))));
}

void Chunk::Draw()
{
	terrain->Draw();
}
