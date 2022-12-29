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

class Renderer
{
private:
	Camera& m_Camera;
	Object3D& m_Object;
	Shader& m_Shader;
	Texture& m_Texture;
	Transform& m_Transform;

	static const Light m_Light;

public:
	Renderer(Camera& camera, Object3D& object, Transform& transform, Texture& texture, Shader& shader) : m_Camera(camera), m_Object(object), m_Texture(texture), m_Transform(transform), m_Shader(shader) {}

	void Draw(glm::vec4 clippingPlane);

	void Clear() const;
};

