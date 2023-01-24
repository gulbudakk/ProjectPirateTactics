#include "Input.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Application.h"
#include <iostream>

int Input::GetKey(const KeyCode key)
{
	auto* inputWindow = static_cast<GLFWwindow*>(&Application::GetWindow());
	auto state = glfwGetKey(inputWindow, static_cast<int32_t>(key));

	return state;
}

int Input::GetMouseButton(const MouseCode button)
{
	auto* inputWindow = static_cast<GLFWwindow*>(&Application::GetWindow());
	auto state = glfwGetMouseButton(inputWindow, static_cast<int32_t>(button));
	return state;
}

glm::vec2 Input::GetMousePosition()
{
	auto* inputWindow = static_cast<GLFWwindow*>(&Application::GetWindow());
	double xpos, ypos;
	glfwGetCursorPos(inputWindow, &xpos, &ypos);

	glm::vec2 mousePos((float)xpos, (float)ypos);

	return mousePos;
}

void Input::SetMousePosition(int width, int height) {
	glfwSetCursorPos(&Application::GetWindow(), width, height);
}

void Input::SetInputMode(int mode, int value) {
	glfwSetInputMode(&Application::GetWindow(), mode, value);
}