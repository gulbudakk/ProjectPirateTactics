#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Light
{
private:
	vec3 m_Color;
	vec3 m_Position;
	float m_Power;
public:
	Light(vec3 color, vec3 position, float power) : m_Color(color), m_Position(position), m_Power(power){}

	const vec3 GetColor() const { return m_Color; }
	const vec3 GetPosition() const  { return m_Position; }
	const float GetPower() const { return m_Power; }
};

