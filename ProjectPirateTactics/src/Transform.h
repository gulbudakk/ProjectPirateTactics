#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Transform
{
private:
	mat4 m_Model;

public:
	Transform() : m_Model(mat4(1.0f)) {}
	
	mat4 GetModel() const { return m_Model; }
	void SetModel(mat4 model) { m_Model = model; }
};

