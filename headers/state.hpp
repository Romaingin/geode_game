#ifndef STATE_HPP
#define STATE_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "input.hpp"
#include "statemanager.hpp"

class StateManager;

// All states will inherit from it
class State
{
public:
	virtual void Init() {};
	virtual void Display() {};
	virtual void Update(int) {};
	virtual void Clean() {};
	virtual void KeyboardHandler(int) {};
	virtual void AttachManager(StateManager* s) { statemanager = s; }

	State() {}
	virtual ~State() {};

	StateManager* statemanager;
};

#endif
