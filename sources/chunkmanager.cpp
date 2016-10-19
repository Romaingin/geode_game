#include <glm/glm.hpp>
#include <iostream>
#include "chunkmanager.hpp"

Coord ChunkManager::FindChunkCoordinates(glm::vec3 cameraLocation)
{
	return Coord{(int)(cameraLocation.x / (size * space)), (int)(cameraLocation.z / (size * space))};
}

ChunkManager::ChunkManager (int se, int s, double sp, int dr)
{
	seed = se;
	size = s;
	space = sp;
	displayRange = dr;

	terrainShaderProgram = new ShaderProgram("shaders/simple.vert", "shaders/simple.frag", "shaders/simple.geo");

	// Declare uniforms
	char const *uniforms[] = {"projection_matrix", "view_matrix", "model_matrix"};
	terrainShaderProgram->CreateUniforms(uniforms, 3);
}

Chunk* ChunkManager::AddChunk(Coord pos)
{
	// TODO : Load from memory
	displayedChunks[pos] = new Chunk(pos, size, space, seed);

	return displayedChunks[pos];
}

void ChunkManager::RemoveChunk(Coord pos)
{
	displayedChunks.erase(pos);
}

void ChunkManager::LoadTest(glm::vec3 cameraLocation)
{
	// TODO, use coord of last active chunk
}


void ChunkManager::RefreshAll(glm::vec3 cameraLocation)
{
	displayedChunks.clear();

	int xpos = (int)(cameraLocation.x / (size * space));
	int ypos = (int)(cameraLocation.y / (size * space));
	Coord camPos = FindChunkCoordinates(cameraLocation);

	for (int i = -displayRange; i < displayRange + 1; i++)
	{
		for (int j = -displayRange; j < displayRange + 1; j++)
		{
			currentChunk = AddChunk(Coord{xpos + i + camPos.x, ypos + j + camPos.y});
		}
	}
}

void ChunkManager::Draw(Camera *camera)
{
	terrainShaderProgram->Use();

	// Set Uniforms
	terrainShaderProgram->SetMat4Uniform("projection_matrix", camera->GetProjectionMatrix());
	terrainShaderProgram->SetMat4Uniform("view_matrix", camera->GetLookAtMatrix());
	//terrainShaderProgram->SetMat4Uniform("model_matrix", glm::mat4());

	// Iterate through the chunks
	for (std::map<Coord, Chunk*>::iterator it=displayedChunks.begin(); it!=displayedChunks.end(); ++it)
	{
		terrainShaderProgram->SetMat4Uniform("model_matrix", glm::translate(	glm::mat4(),
									glm::vec3((float)(it->first.x * space * size),
									0.0f,
									(float)(it->first.y * space * size))));
		it->second->Draw();
	}
}

void ChunkManager::Clean()
{
	//sceneObjects[i]->Clean();

	terrainShaderProgram->Clean();
}
/*
glm::vec3 getTerrainHeight(glm::vec2 mapPos, )
{

}
*/
