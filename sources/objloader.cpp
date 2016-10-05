#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <string.h>
#include <sstream>
#include <string>
#include <fstream>

// No UVs
bool ObjLoader(const char *path,
    std::vector<glm::vec3> & outVertices,
    std::vector<unsigned int> & outIndices)
{
	std::ifstream in(path, std::ios::in);
	if (!in)
	{
		std::cerr << "Cannot open " << path << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(in, line))
	{
		//check v for vertices
		if (line.substr(0,2)=="v ")
		{
			std::istringstream v(line.substr(2));
			float x, y, z;
			v>>x; v>>y; v>>z;
			outVertices.push_back(glm::vec3(x, y, z));
		}
		//check for faces
		else if(line.substr(0,2)=="f ")
		{
			unsigned int vertexIndex[3], normalIndex[3];
			const char* chh = line.c_str();
			sscanf (chh, "f %d//%d %d//%d %d//%d\n",	&vertexIndex[0], &normalIndex[0],
														&vertexIndex[1], &normalIndex[1],
														&vertexIndex[2], &normalIndex[2] );

			outIndices.push_back(vertexIndex[0] - 1);
			outIndices.push_back(vertexIndex[1] - 1);
			outIndices.push_back(vertexIndex[2] - 1);
		}
	}

	return true;
}