#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Application.h"

using namespace glm;

class Camera {
private:
	mat4 m_Projection;
	mat4 m_View;

	vec2 m_Angle;

	float m_Fov;
	float m_displayRangeMin;
	float m_displayRangeMax;

	vec3 m_Position;
	vec3 m_Right;
	vec3 m_Up;
	vec3 m_Direction;

	void ComputeVP();
	void ComputeProjection();
	void ComputeView();
	void ComputeRight();
	void ComputeUp();
	void ComputeDirection();

public:
	Camera(vec3 position, vec2 angle, float fov, float minDisplayRange, float maxDisplayRange);

	~Camera() = default;

	mat4 GetProjection();
	void SetProjection(mat4 projection);

	mat4 GetView();
	void SetView(mat4 view);

	mat4 GetMVP(mat4 model);

	vec3 GetPosition();
	void SetPosition(vec3 newPosition);

	vec2 GetAngle();
	void SetAngle(vec2 angle);

	vec3 GetRight();

	vec3 GetDirection();
};

