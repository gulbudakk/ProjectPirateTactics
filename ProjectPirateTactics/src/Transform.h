#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Transform
{
private:
	mat4 m_Model = mat4(1);
	vec3 m_position = vec3(0);
	vec3 m_rotation = vec3(0);
	vec3 m_scale = vec3(1);

public:
	Transform(){}
	
	mat4 GetModel() const { return m_Model; }

	mat4 CalculateModel() {
		m_Model = mat4(1.0f);
		m_Model = translate(m_Model, m_position);
		m_Model = rotate(m_Model, radians(m_rotation.x), vec3(1, 0, 0));
		m_Model = rotate(m_Model, radians(m_rotation.y), vec3(0, 1, 0));
		m_Model = rotate(m_Model, radians(m_rotation.z), vec3(0, 0, 1));
		m_Model = glm::scale(m_Model, m_scale);
		return m_Model;
	}

	vec3 GetPosition() { return m_position; }
	vec3 GetRotation() { return m_rotation; }
	vec3 GetScale() { return m_scale; }

	void SetPosition(vec3 position) {
		m_position = position;
		CalculateModel();
	}

	void SetRotation(vec3 rotation) {
		m_rotation = rotation;
		CalculateModel();
	}

	void SetScale(vec3 scale) {
		m_scale = scale;
		CalculateModel();
	}
};

