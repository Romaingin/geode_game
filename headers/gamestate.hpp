#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "state.hpp"
#include "shaderprogram.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "chunkmanager.hpp"

// Main drawing state (in game mode)
class GameState : public State
{
public:
	virtual void Init();
	virtual void Display();
	virtual void Update(int dt);
	virtual void Clean();
	virtual void KeyboardHandler(int dt);

	// Graphics
	Camera *camera;
	glm::mat4 ProjectionMatrix;
	ShaderProgram *simpleShaderProgram;

	// Scene
	ChunkManager *chunkmanager;
	std::vector<Object *> sceneObjects;
	GLuint vertexbuffer;
};

#endif
