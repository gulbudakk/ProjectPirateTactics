#include "Time.h"
#include <iostream>

double Time::lastTime = 0;
double Time::currentTime = 0;
double Time::deltaTime = 0;

int Time::nbFrames = 0;
double Time::timeSum = 0;

void Time::Tick() {
	// Compute time difference between current and last frame
	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	CountFPS(deltaTime);
}

double Time::GetDeltaTime() {
	return deltaTime;
}

void Time::CountFPS(double deltaTime) {
	nbFrames++;
	timeSum += deltaTime;
	if (timeSum >= 1.0f) { // If last prinf() was more than 1sec ago
		// printf and reset
		std::cout << "FPS: " << nbFrames << std::endl;
		nbFrames = 0;
		timeSum = 0;
	}
}

