#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "input.hpp"
#include "timer.hpp"
#include "statemanager.hpp"
#include "gamestate.hpp"

class Program
{
public:
	bool Init();
	void Run();
	Program(int w, int h) { windowWidth = w; windowHeight = h;};
private:
	// Window
	GLFWwindow* window;
	int windowWidth;
	int windowHeight;
	Input *input;
	Timer *timer;

	// States
	StateManager *statemanager;
};

#endif
