#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <iostream>
#include <string>
#include <map>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
	void Use();
	void CreateUniforms(char const **uniformNames, int size);
	void SetMat4Uniform(const char *name, const glm::mat4 &matrix);
	ShaderProgram(const char * vertexFilePath, const char *fragmentFilePath, const char *geometryFilePath);
	void Clean() { glDeleteProgram(programID); }
private:
	GLuint programID;
	std::map<char, GLuint> uniformList;
};

#endif