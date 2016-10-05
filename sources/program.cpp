#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>

#include "program.hpp"
#include "shader.hpp"

using namespace glm;
using namespace std;

bool Program::Init()
{
	// Initialize GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW" );
		getchar();
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( windowWidth, windowHeight, "Application", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible." );
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW");
		getchar();
		glfwTerminate();
		return false;
	}

	// Handlers
	input = new Input();
	input->SetWindows(window);

	timer = new Timer();
	timer->Start();

	// States
	statemanager = new StateManager();
	statemanager->Init(statemanager, input);

	statemanager->AddState("game_state", new GameState());
	statemanager->AttachManagerState("game_state");
	statemanager->SetActiveState("game_state");
	statemanager->InitActiveState();

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// The input sends the stack to the statemanager
	glfwSetKeyCallback(window, input->KeyboardStack);

	glfwSwapInterval(0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	return true;
}

void Program::Run()
{
	do{
		// Time settings
		int dt = timer->GetDelaTimeMs();
		// std::cout << 1000.0 / (float)dt << " FPS"<< std::endl;

		if (dt == 0)
			dt = 1;

		glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
		// Call the current state
		statemanager->Display();
		statemanager->Update(dt);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0 );

	statemanager->Clean();
	fprintf(stderr, "Cleaned\n");

	glfwTerminate();
}
