#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "timer.hpp"

void Timer::Start()
{
	startTime = std::chrono::high_resolution_clock::now();
	previousTime = startTime;
}

int Timer::GetElapsedTimeMs()
{
	auto D = std::chrono::high_resolution_clock::now() - startTime;
	return std::chrono::duration_cast<std::chrono::milliseconds>(D).count();
}

// Also update previous time
int Timer::GetDelaTimeMs()
{
	auto T = std::chrono::high_resolution_clock::now();
	auto D = T - previousTime;
	previousTime = T;
	return std::chrono::duration_cast<std::chrono::milliseconds>(D).count();
}