#ifndef CHUNK_MANAGER_HPP
#define CHUNK_MANAGER_HPP

#include <vector>
#include <map>
#include <string>
#include "chunk.hpp"
#include "shaderprogram.hpp"
#include "camera.hpp"

class ChunkManager {
private:
	std::map<Coord, Chunk*> displayedChunks;
	int size;
	double space;
	int seed;
	int displayRange;
	Chunk* currentChunk;
	ShaderProgram *terrainShaderProgram;

	void WithinRange(glm::vec3 cameraLocation);
	Chunk* AddChunk(Coord pos);
	void RemoveChunk(Coord pos);
	Coord FindChunkCoordinates(glm::vec3 cameraLocation);
public:
	void LoadTest(glm::vec3 cameraLocation);
	void RefreshAll(glm::vec3 cameraLocation);
	void Draw(Camera *camera);
	void Clean();

	ChunkManager (int se, int s, double sp, int dr);
	~ChunkManager () {}
};

#endif
