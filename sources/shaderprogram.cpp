#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include "shaderprogram.hpp"
#include "shader.hpp"

ShaderProgram::ShaderProgram(const char *vertexFilePath, const char *fragmentFilePath, const char *geometryFilePath)
{
	programID = LoadShaders(vertexFilePath, fragmentFilePath, geometryFilePath);
}

void ShaderProgram::Use()
{
	glUseProgram(programID);
}

void ShaderProgram::CreateUniforms(char const **uniformNames, int size)
{
	for (int i = 0; i < size ; i++)
	{
		char const *name = uniformNames[i];
		uniformList[*name] = glGetUniformLocation(programID, name);
	}
}

void ShaderProgram::SetMat4Uniform(const char *name, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(uniformList[*name], 1, GL_FALSE, &matrix[0][0]);
	
}