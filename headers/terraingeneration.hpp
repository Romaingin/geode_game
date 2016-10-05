#ifndef TERRAIN_GENERATION_HPP
#define TERRAIN_GENERATION_HPP

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

bool GenerateTerrain(int, int, int, float, std::vector<glm::vec3>&, std::vector<unsigned int>&);

#endif
