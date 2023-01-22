#pragma once
#include <glm/glm.hpp>
#include "../Camera.h"
#include "../GameObject.h"

class CameraMovement : public GameObject
{
private:
	Camera& m_Camera;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	bool isMovementActive = false;

	void ComputeMatrices();
protected:
	void Update();
public:
	CameraMovement(Camera& camera) : m_Camera(camera) {}
	void Clear() {};
};

