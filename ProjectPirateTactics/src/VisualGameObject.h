#pragma once
#include "GameObject.h"
#include "Camera.h"

class VisualGameObject : public GameObject {
protected:
	Camera& m_Camera;
	Transform m_Transform;
	Object3D& m_Object;
	Shader& m_Shader;
	Renderer m_Renderer;
	Texture& m_Texture;
protected:
	VisualGameObject(Camera& camera, Object3D& object, Texture& texture, Shader& shader) :m_Camera(camera), m_Object(object), m_Texture(texture), m_Shader(shader), m_Renderer(Renderer(camera, object, m_Transform, texture, shader)) {}

	VisualGameObject(VisualGameObject& other) :m_Camera(other.m_Camera), m_Object(other.m_Object), m_Texture(other.m_Texture), m_Shader(other.m_Shader), m_Renderer(Renderer(m_Camera, m_Object, m_Transform, m_Texture, m_Shader)) {}

	virtual void Update() = 0;

	void Swap(VisualGameObject& other) {
		m_Camera = other.m_Camera;
		m_Transform = other.m_Transform;
		m_Object = other.m_Object;
		m_Shader = other.m_Shader;
		m_Texture = other.m_Texture;
		Renderer m_Renderer(m_Camera, m_Object, m_Transform, m_Texture, m_Shader);
	}
public:
	Transform& GetTransform() { return m_Transform; }
	void Clear() { m_Renderer.Clear(); }

	void Tick(glm::vec4 clippingPlane) {
		Update();

		m_Renderer.Draw(clippingPlane);
	}

	virtual VisualGameObject& operator=(VisualGameObject& other) = 0;
};
