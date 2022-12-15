#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Object3D.h"
#include "Texture.h"

class Renderer
{
private:
	Camera& m_Camera;
	Object3D& m_Object;
	Texture& m_Texture;
	mat4 m_Model;
public:
	Renderer(Camera& camera, Object3D& object, Texture& texture) : m_Camera(camera), m_Object(object), m_Texture(texture) {
		m_Model = mat4(1.0f);
	}

	void Draw();

	void Clear() const;
};

