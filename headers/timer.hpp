#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer
{
public:
	void Start();
	int GetElapsedTimeMs();
	int GetDelaTimeMs();

	Timer() {};
	~Timer();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
};

#endif