#include "CameraMovement.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Input.h"
#include "../Camera.h"
#include "../Application.h"
#include "../Time.h"
using namespace glm;

void CameraMovement::ComputeMatrices() {

	float deltaTime = Time::GetDeltaTime();

	// Get mouse position
	vec2 mousePosition = Input::GetMousePosition();

	// Reset mouse position for next frame
	Input::SetMousePosition(Application::GetWidth()/2, Application::GetHeight()/2);

	// Compute new orientation
	vec2 newAngle(m_Camera.GetAngle().x + mouseSpeed * float(Application::GetWidth()/2 - mousePosition.x), m_Camera.GetAngle().y + mouseSpeed * float(Application::GetHeight()/2 - mousePosition.y));
	m_Camera.SetAngle(newAngle);

	// Move forward
	if (Input::GetKey(KeyCode::W)) {
		 m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetDirection() * deltaTime * speed);
	}
	// Move backward
	if (Input::GetKey(KeyCode::S)) {
		m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetDirection() * deltaTime * speed);
	}
	// Strafe right
	if (Input::GetKey(KeyCode::D)) {
		m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetRight() * deltaTime * speed);
	}
	// Strafe left
	if (Input::GetKey(KeyCode::A)) {
		m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetRight() * deltaTime * speed);
	}
}

void CameraMovement::Update() {
	ComputeMatrices();
}
