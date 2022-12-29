#include "Camera.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Application.h"

using namespace std;
using namespace glm;

Camera::Camera(vec3 position, vec2 angle, float fov, float minDisplayRange, float maxDisplayRange) : m_Position(position), m_Angle(angle), m_Fov(fov), m_displayRangeMin(minDisplayRange), m_displayRangeMax(maxDisplayRange)
{
	ComputeVP();
}

void Camera::ComputeVP() {
	ComputeDirection();
	ComputeRight();
	ComputeUp();
	ComputeView();
	ComputeProjection();
}

void Camera::ComputeProjection() {
	m_Projection = glm::perspective(glm::radians(m_Fov), Application::GetRatio(), m_displayRangeMin, m_displayRangeMax);
}

void Camera::ComputeView() {
	m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
}

void Camera::ComputeRight() {
	m_Right = glm::vec3(sin(m_Angle.x - 3.14f / 2.0f), 0, cos(m_Angle.x - 3.14f / 2.0f));
}

void Camera::ComputeUp() {
	m_Up = glm::cross(m_Right, m_Direction);
}

void Camera::ComputeDirection() {
	vec3 direction(cos(m_Angle.y) * sin(m_Angle.x), sin(m_Angle.y), cos(m_Angle.y) * cos(m_Angle.x));
	m_Direction = direction;
}

mat4 Camera::GetProjection() { return m_Projection; }
void Camera::SetProjection(mat4 projection) {
	m_Projection = projection;
	ComputeVP();
}

mat4 Camera::GetView() { return m_View; }
void Camera::SetView(mat4 view) {
	m_View = view;
	ComputeVP();
}

mat4 Camera::GetMVP(mat4 model) {
	return m_Projection * m_View * model;
}

vec3 Camera::GetPosition() { return m_Position; }
void Camera::SetPosition(vec3 newPosition) {
	m_Position = newPosition;
	ComputeVP();
}

vec2 Camera::GetAngle() {
	return m_Angle;
}

void Camera::SetAngle(vec2 angle) {
	m_Angle = angle;
	ComputeVP();
}

vec3 Camera::GetRight() { return m_Right; }
vec3 Camera::GetDirection() { return m_Direction; }

vec3 Camera::GetUp()
{
	return m_Up;
}

void Camera::SetUp(vec3 newUp)
{
	m_Up = newUp;
	ComputeVP();
}
