#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Object3D.h"
#include "Texture.h"
#include "Transform.h"

class Renderer
{
private:
	Camera& m_Camera;
	Object3D& m_Object;
	Texture& m_Texture;
	Transform& m_Transform;

public:
	Renderer(Camera& camera, Object3D& object, Transform& transform,Texture& texture) : m_Camera(camera), m_Object(object), m_Texture(texture), m_Transform(transform) {}

	void Draw();

	void Clear() const;
};

