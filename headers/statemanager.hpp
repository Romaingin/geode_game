#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>

#include "state.hpp"
#include "gamestate.hpp"
#include "input.hpp"

class State;

class StateManager
{
public:
	static std::map<char, State*> stateStack;
	static const char *activeState;

	void AddState(const char *s, State *S);
	void AttachManagerState(const char *s);
	void DeleteState(const char *s);
	void SetActiveState(const char *s);
	State* GetActiveState();
	void InitActiveState();

	void Init(StateManager *s, Input *i) { 	statemanager = s;
											input = i; }
	void Display();
	void Update(int dt);
	void Clean();

	Input* GetInput() { return input; }

	StateManager();
	~StateManager();

private:
	StateManager *statemanager;
	Input *input;
};

#endif
