#pragma once
#include <GLFW/glfw3.h>


class Time 
{
private:
	static double lastTime;
	static double currentTime;
	static double deltaTime;
	static double timeSum;
	static int nbFrames;

	static void CountFPS(double deltaTime);
public:
	static void Tick();

	static double GetDeltaTime();
};