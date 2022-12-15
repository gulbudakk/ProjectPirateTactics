#pragma once
#include <glm/glm.hpp>
#include "../Camera.h"

class CameraMovement
{
private:
	Camera& m_Camera;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	void ComputeMatrices();
public:
	CameraMovement(Camera& camera) : m_Camera(camera) {}
	void Tick();
};

