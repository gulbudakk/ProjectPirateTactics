#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "OrthographicRenderer.h"

class OrthographicObject : public GameObject {
protected:
	Camera& m_Camera;
	Transform m_Transform;
	Object3D& m_Object;
	Shader& m_Shader;
	OrthographicRenderer m_Renderer;
	Texture& m_Texture;
protected:
	OrthographicObject(Camera& camera, Object3D& object, Texture& texture, Shader& shader) :m_Camera(camera), m_Object(object), m_Texture(texture), m_Shader(shader), m_Renderer(OrthographicRenderer(camera, object, m_Transform, texture, shader)) {}

	OrthographicObject(OrthographicObject& other) :m_Camera(other.m_Camera), m_Object(other.m_Object), m_Texture(other.m_Texture), m_Shader(other.m_Shader), m_Renderer(OrthographicRenderer(m_Camera, m_Object, m_Transform, m_Texture, m_Shader)) {}

	virtual void Update() = 0;

	void Swap(OrthographicObject& other) {
		m_Camera = other.m_Camera;
		m_Transform = other.m_Transform;
		m_Object = other.m_Object;
		m_Shader = other.m_Shader;
		m_Texture = other.m_Texture;
		OrthographicRenderer m_Renderer(m_Camera, m_Object, m_Transform, m_Texture, m_Shader);
	}
public:
	Transform& GetTransform() { return m_Transform; }
	void Clear() { m_Renderer.Clear(); }

	void Tick(glm::vec4 clippingPlane) {
		Update();

		m_Renderer.Draw(clippingPlane);
	}

	virtual OrthographicObject& operator=(OrthographicObject& other) = 0;
};

