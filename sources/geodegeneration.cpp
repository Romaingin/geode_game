#include <iostream>
#include <sstream>

#include "geodegeneration.hpp"
#include "perlinnoise.hpp"

using namespace std;

double GenTerrainNoise(PerlinNoise *noiseGen, double x, double y, double z)
{
	double noise = noiseGen->OctaveSmoothPerlin(x, y, z, 4, 0.7);

	if (noise < 0.8)
	{
		noise = 1.1719 * noise * noise * noise - 0.7813 * noise * noise + 0.7;
	}

	return 0.2 * noise;
}

void GenerateGeode(float radius, int detailLevel,
		vector<glm::vec3> &outVertices,
		vector<unsigned int> &outIndices)
{
	PerlinNoise noiseGen = PerlinNoise(250);
	GeodeGeometryProvider::Icosahedron(outVertices, outIndices);

	// Subdivize the icosahedron
	for (int i = 0; i < detailLevel; i++)
	{
		GeodeGeometryProvider::Subdivide(outVertices, outIndices, true);
	}

	// Normalize then add relief
	for (uint i = 0; i < outVertices.size(); i++)
	{
		outVertices[i] = glm::normalize(outVertices[i]);
		outVertices[i]= radius * (1 - (float)GenTerrainNoise(&noiseGen, outVertices[i].x, outVertices[i].y, outVertices[i].z)) * outVertices[i];
	}
}

int GeodeGeometryProvider::GetMidpointIndex(map<string, int> &midpointIndices, vector<glm::vec3> &vertices, int i0, int i1)
{
	stringstream s;
	s << min(i0, i1) << "_" << max(i0, i1);
	string edgeKey = s.str();
	int midpointIndex = -1;

	if (midpointIndices.count( edgeKey ) == 1)
	{
		midpointIndex = midpointIndices[edgeKey];
	} else {
		glm::vec3 v0 = vertices[i0];
		glm::vec3 v1 = vertices[i1];

		glm::vec3 midpoint = (v0 + v1) * 0.5f;

		for(std::vector<int>::size_type i = 0; i != vertices.size(); i++) {
			if (vertices[i] == midpoint)
			{
				return i;
			}
		}

		midpointIndex = vertices.size();
		vertices.push_back(midpoint);
		midpointIndices[edgeKey] = midpointIndex;
	}

	return midpointIndex;
}


void GeodeGeometryProvider::Subdivide(vector<glm::vec3> &vectors, vector<unsigned int> &indices, bool removeSourceTriangles)
{
	std::map<string, int> midpointIndices;
	vector<unsigned int> newIndices(indices.size() * 4);

	if (!removeSourceTriangles)
		newIndices.insert(newIndices.end(), indices.begin(), indices.end());

	for (uint i = 0; i < indices.size() - 2; i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		int m01 = GetMidpointIndex(midpointIndices, vectors, i0, i1);
		int m12 = GetMidpointIndex(midpointIndices, vectors, i1, i2);
		int m02 = GetMidpointIndex(midpointIndices, vectors, i2, i0);

		auto ni = vector<int>{
			i0,m01,m02,
			i1,m12,m01,
			i2,m02,m12,
			m02,m01,m12
		};

		newIndices.insert(newIndices.end(),	ni.begin(), ni.end());
	}

	indices.clear();
	indices = newIndices;
}

void GeodeGeometryProvider::Icosahedron(vector<glm::vec3> &vertices, vector<unsigned int> &indices)
{
	auto newIndices = vector<int>{
			0,4,1,
			0,9,4,
			9,5,4,
			4,5,8,
			4,8,1,
			8,10,1,
			8,3,10,
			5,3,8,
			5,2,3,
			2,7,3,
			7,10,3,
			7,6,10,
			7,11,6,
			11,0,6,
			0,1,6,
			6,1,10,
			9,0,11,
			9,11,2,
			9,2,5,
			7,2,11
		};

	indices.insert(indices.end(), newIndices.begin(), newIndices.end());

		// .Select(i => i + vertices.size())
		// );

	float X = 0.525731112119133606f;
	float Z = 0.850650808352039932f;

	auto newVertices = vector<glm::vec3>{
			glm::vec3(-X, 0, Z),
			glm::vec3(X, 0, Z),
			glm::vec3(-X, 0, -Z),
			glm::vec3(X, 0, -Z),
			glm::vec3(0, Z, X),
			glm::vec3(0, Z, -X),
			glm::vec3(0, -Z, X),
			glm::vec3(0, -Z, -X),
			glm::vec3(Z, X, 0),
			glm::vec3(-Z, X, 0),
			glm::vec3(Z, -X, 0),
			glm::vec3(-Z, -X, 0)
		};

	vertices.insert(vertices.end(), newVertices.begin(), newVertices.end());
}
