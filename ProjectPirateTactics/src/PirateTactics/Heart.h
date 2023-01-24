#pragma once
#include "../VisualGameObject.h"
#include "../OrthographicRenderer.h"
#include "../OrthographicObject.h"

class Heart : public OrthographicObject
{
protected:
	void Update();

	float speed = 30;
public:
	Heart(Camera& camera, Object3D& object, Texture& texture, Shader& shader) : OrthographicObject(camera, object, texture, shader) {}
	Heart(Heart& other) : OrthographicObject(other) {}

	OrthographicObject& operator=(OrthographicObject& other)
	{
		OrthographicObject::Swap(other);

		return *this;
	}
};
