#pragma once
#include "GameObject.h"

class VisualGameObject : public GameObject {
protected:
	Transform m_Transform;
	Object3D& m_Object;
	Renderer m_Renderer;
	Texture& m_Texture;
protected:
	VisualGameObject(Camera& camera, Object3D& object, Texture& texture, Shader& shader) : m_Object(object), m_Texture(texture), m_Renderer(Renderer(camera, object, m_Transform, texture, shader)) {}

	virtual void Update() = 0;
public:
	Transform& GetTransform() { return m_Transform; }
	void Clear() { m_Renderer.Clear(); }

	void Tick() {
		Update();

		m_Renderer.Draw();
	}
};
