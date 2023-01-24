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

	Texture& m_reflectionTexture;
	Texture& m_refractionTexture;
	Texture& m_dudvTexture;
	Texture& m_normalmapTexture;

	float* m_moveFactor;

public:
	WaterRenderer(Camera& camera, Object3D& object, Transform& transform, Shader& shader, Texture& reflectionTexture, Texture& refractionTexture, Texture& dudvTexture, Texture& normalTexture, float* moveFactor) : m_Camera(camera), m_Object(object), m_Transform(transform), m_Shader(shader), m_reflectionTexture(reflectionTexture), m_refractionTexture(refractionTexture), m_dudvTexture(dudvTexture), m_normalmapTexture(normalTexture), m_moveFactor(moveFactor) {}

	void Draw();

	void Clear() const;
};

