#ifndef INPUT_HPP
#define INPUT_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <map>
#include <GLFW/glfw3.h>

class Input
{
public:
	glm::vec2 GetMousePos();
	glm::vec2 GetDisplacement(float deltaTime);
	glm::vec2 GetWindowSize();
	void CenterCursor();
	void SetScreenSize(int w, int h);
	void SetWindows(GLFWwindow* w) { window = w; }
	static void KeyboardStack(GLFWwindow* window, int key, int scancode, int action, int mods);
	std::map<int,int> GetKeyStack() { return keyStack; }
	
	Input();
private:
	GLFWwindow* window;
	static std::map<int,int> keyStack;
};

#endif