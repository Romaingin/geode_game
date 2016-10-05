#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "object.hpp"
#include "objloader.hpp"

// The data is given to it
Object::Object(std::vector<glm::vec3>& vertices,
				std::vector<unsigned int>& indices,
				GLenum pType)
{
	modelMatrix = glm::mat4();
	primitiveType = pType;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0] , GL_STATIC_DRAW);

	vertexCount = indices.size();
}

void Object::Draw()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	// Draw the primitives
	glDrawElements(
		primitiveType,      // mode
		vertexCount,    	// count
		GL_UNSIGNED_INT,  // type
		(void*)0           	// element array buffer offset
	);

	glDisableVertexAttribArray(0);
}

void Object::Clean()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
}
