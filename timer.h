#pragma once
class Timer
{
	float totalTime = 0.0f;

public:
	void Update(float deltaTime);
	void Reset();
	bool CheckTime(float neededTime);
};

