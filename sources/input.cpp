#include "input.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::map<int,int> Input::keyStack = {};

Input::Input() {}

glm::vec2 Input::GetMousePos()
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	return glm::vec2((float)xpos, (float)ypos);;
}

glm::vec2 Input::GetDisplacement(float deltaTime)
{
	glm::vec2 screenSize = GetWindowSize();
	return (screenSize * 0.5f - GetMousePos()) / deltaTime;
}

glm::vec2 Input::GetWindowSize()
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return glm::vec2(width, height);
}

void Input::CenterCursor()
{
	glm::vec2 screenSize = GetWindowSize();
	glfwSetCursorPos(window, screenSize.x * 0.5f, screenSize.y * 0.5f);
}

void Input::KeyboardStack(GLFWwindow*, int key, int, int action, int)
{
	keyStack[key] = action;
}
