#include "timer.h"
void Timer::Update(float deltaTime) {
	totalTime += deltaTime;
}

void Timer::Reset() {
	totalTime = 0.0f;
}

bool Timer::CheckTime(float neededTime) {
	if (totalTime > neededTime)
	{
		Reset();
		return 1;
	}
	return 0;
}