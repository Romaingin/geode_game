#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>

class Object
{
public:
	void Draw();
	GLuint GetVaoID() { return vertexBuffer; }
	glm::mat4 GetModelMatrix() { return modelMatrix; }
	void SetModelMatrix(glm::mat4 m) { modelMatrix = m; }
	void Clean();

	Object(std::vector<glm::vec3>& vertices,
				std::vector<unsigned int>& indices,
				GLenum pType);
private:
	GLenum primitiveType;
	GLuint VertexArrayID, vertexBuffer, indexBuffer;
	glm::mat4 modelMatrix;
	unsigned int vertexCount;
};

#endif
