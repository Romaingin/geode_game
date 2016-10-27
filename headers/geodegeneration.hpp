#ifndef GEODE_GENERATION_HPP
#define GEODE_GENERATION_HPP

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>

// Specify the radius, and the level of details
void GenerateGeode(float radius, int detailLevel, std::vector<glm::vec3> &outVertices, std::vector<unsigned int> &outIndices);

class GeodeGeometryProvider
{
private:
	static int GetMidpointIndex(std::map<std::string, int> &midpointIndices, std::vector<glm::vec3> &vertices, int i0, int i1);
public:
	static void Subdivide(std::vector<glm::vec3> &vectors, std::vector<unsigned int> &indices, bool removeSourceTriangles);
	static void Icosahedron(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices);
};

#endif
