#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "object.hpp"

struct Coord {
	int x, y;

	bool operator=(const Coord &o) {
		return x == o.x && y == o.y;
	}

	bool operator<(const Coord &o) const {
		return x < o.x || (x == o.x && y < o.y);
	}
};

class Chunk {
public:
	void Draw();
	glm::mat4 GetModelMatrix() { return terrain->GetModelMatrix(); }

	Chunk(Coord c, int s, double sp, int se);
	~Chunk() {}
private:
	Coord coordinates;
	int size;
	double space;
	int seed;

	// Terrain related
	Object *terrain;
	std::vector<glm::vec3> terrainVertices;
	std::vector<unsigned int> terrainIndices;
};

#endif
