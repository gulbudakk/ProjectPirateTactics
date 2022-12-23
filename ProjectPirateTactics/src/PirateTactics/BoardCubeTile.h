#pragma once
#include "../VisualGameObject.h"

class BoardCubeTile : public VisualGameObject
{
protected:
	void Update(){}
public:
	BoardCubeTile(Camera& camera, Object3D& object, Texture& texture, Shader& shader) : VisualGameObject(camera, object, texture, shader){}
	BoardCubeTile(BoardCubeTile& other) : VisualGameObject(other) {}

	VisualGameObject & operator=(VisualGameObject& other);
};

