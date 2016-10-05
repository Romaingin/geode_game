#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "statemanager.hpp"

std::map<char, State*> StateManager::stateStack = {};
const char *StateManager::activeState = new char();

StateManager::StateManager() {}

StateManager::~StateManager() {}

void StateManager::AddState(const char *s, State *S)
{
	StateManager::stateStack[*s] = S;
}

void StateManager::AttachManagerState(const char *s)
{
	StateManager::stateStack[*s]->AttachManager(statemanager);
}

void StateManager::DeleteState(const char *s)
{
	std::map<char,State*>::iterator it = StateManager::stateStack.find(*s);
    StateManager::stateStack.erase(it);
}

void StateManager::SetActiveState(const char *s)
{
	StateManager::activeState = s;
}

State* StateManager::GetActiveState()
{
	return StateManager::stateStack[*StateManager::activeState];
}

void StateManager::InitActiveState()
{
	StateManager::stateStack[*StateManager::activeState]->Init();
}


void StateManager::Display()
{
	StateManager::stateStack[*StateManager::activeState]->Display();
}

void StateManager::Update(int dt)
{
	StateManager::stateStack[*StateManager::activeState]->Update(dt);
}

void StateManager::Clean()
{
	// TODO Clean all
	StateManager::stateStack[*StateManager::activeState]->Clean();
}
