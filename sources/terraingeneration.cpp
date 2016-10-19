#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "terraingeneration.hpp"
#include "perlinnoise.hpp"

using namespace glm;
using namespace std;

double GenTerrainNoise(PerlinNoise *noiseGen, double x, double y)
{

	double noise = noiseGen->OctaveSmoothPerlin(x, y, 0.0, 5, 0.5);

	if (noise < 0.8)
	{
		noise = 1.1719 * noise * noise * noise - 0.7813 * noise * noise + 0.7;
	}

	return 100 * noise - 60;
}

bool GenerateTerrain(int x, int y, int size, float space,
	vector<vec3> &outVertices,
	vector<unsigned int> &outIndices)
{
	PerlinNoise noiseGen = PerlinNoise(1000);
	double scalingFactor = 0.015;

	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			outVertices.push_back(vec3(space * i, GenTerrainNoise(&noiseGen, scalingFactor * space * (i + x * size),
															scalingFactor * space * (j + y * size)), space * j));

			// Index the two triangles
			outIndices.push_back((size+1) * j + i);
			outIndices.push_back((size+1) * (j + 1) + i);
			outIndices.push_back((size+1) * j + i + 1);

			outIndices.push_back((size+1) * j + i + 1);
			outIndices.push_back((size+1) * (j + 1) + i);
			outIndices.push_back((size+1) * (j + 1) + i + 1);
		}

		// One more at the end
		outVertices.push_back(vec3(space * size, GenTerrainNoise(&noiseGen, scalingFactor * space * (size + x * size),
											scalingFactor * space * (j + y * size)), space * j));
	}

	// Extra row
	for (int k = 0; k < size + 1; k++)
	{
		outVertices.push_back(vec3(space * k, GenTerrainNoise(&noiseGen, scalingFactor * space * (k + x * size),
											scalingFactor * space * (size + y * size)), space * size));
	}

	return true;
}
