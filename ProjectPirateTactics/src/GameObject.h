#pragma once
#include "Transform.h"
#include "Object3D.h"
#include "Renderer.h"

class GameObject
{
protected:
	virtual void Update() = 0;

public:
	virtual void Tick(glm::vec4 clippingPlane) {
		Update();
	}
	virtual void Clear() = 0;
};