#pragma once
#include "../VisualGameObject.h"
#include "../OrthographicRenderer.h"
#include "../OrthographicObject.h"

class Dice : public OrthographicObject
{
protected:
	void Update() {}
public:
	Dice(Camera& camera, Object3D& object, Texture& texture, Shader& shader) : OrthographicObject(camera, object, texture, shader) {}
	Dice(Dice& other) : OrthographicObject(other) {}

	OrthographicObject& operator=(OrthographicObject& other)
	{
		OrthographicObject::Swap(other);

		return *this;
	}
};
