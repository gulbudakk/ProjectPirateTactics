#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Object3D.h"
#include "Texture.h"
#include "Transform.h"
#include "Light.h"

class WaterRenderer
{
private:
	Camera& m_Camera;
	Object3D& m_Object;
	Shader& m_Shader;
	Transform& m_Transform;


public:
	WaterRenderer(Camera& camera, Object3D& object, Transform& transform, Shader& shader) : m_Camera(camera), m_Object(object), m_Transform(transform), m_Shader(shader) {}

	void Draw();

	void Clear() const;
};

