#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "gamestate.hpp"
#include "objloader.hpp"
#include "terraingeneration.hpp"

void GameState::Init()
{
	// Camera
	camera = new Camera();

	// Create scene
	chunkmanager = new ChunkManager(501, 60, 2.0, 1);
	chunkmanager->RefreshAll(camera->GetPosition());
}

void GameState::Display()
{
	// Draw the terrain
	chunkmanager->Draw(camera);

	glDisableVertexAttribArray(0);
}

void GameState::Update(int dt)
{
	// Keyboard input
	KeyboardHandler(dt);
	//chunkmanager->RefreshAll(camera->GetPosition());
	Input *i = statemanager->GetInput();
	camera->UpdateAimVect(i->GetDisplacement((float)dt));
	i->CenterCursor();
}

void GameState::Clean()
{
	for(std::vector<int>::size_type i = 0; i != sceneObjects.size(); i++) {
		sceneObjects[i]->Clean();
	}

	simpleShaderProgram->Clean();
}

void GameState::KeyboardHandler(int dt)
{
	float stepFront = 0.0f;
	float stepSide = 0.0f;
	float walkSpeed = 0.02f * dt;

	// Map of pressed Keys
	std::map<int,int> keystack = statemanager->GetInput()->GetKeyStack();

	for (std::map<int,int>::iterator it=keystack.begin(); it!=keystack.end(); ++it)
	{
		if (it->second != GLFW_RELEASE)
		{
			switch (it->first)
			{
				case GLFW_KEY_W:
					stepFront += walkSpeed;
					break;
				case GLFW_KEY_S:
					stepFront -= walkSpeed;
					break;
				case GLFW_KEY_A:
					stepSide -= walkSpeed;
					break;
				case GLFW_KEY_D:
					stepSide += walkSpeed;
					break;
			}
		}
	}

	camera->Walk(stepFront, stepSide, 0);
}
