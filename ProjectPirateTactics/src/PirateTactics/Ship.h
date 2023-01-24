#pragma once

#include "../VisualGameObject.h"
#include "../Tilemap.h"

class Ship : public VisualGameObject{

protected:
	Tilemap& m_obstacleTilemap;
	int current_row = 1, current_col = 0;

	void Update();
public:
	Ship(Camera& camera, Object3D& object, Texture& texture, Shader& shader, Tilemap& obstacleTilemap) : m_obstacleTilemap(obstacleTilemap), VisualGameObject(camera, object, texture, shader) {}
	Ship(Ship& other) : m_obstacleTilemap(other.m_obstacleTilemap), VisualGameObject(other) {}

	VisualGameObject& operator=(VisualGameObject& other);
	bool MoveOnGrid(int row, int col);

	void GetLocation(int& row, int& col) {
		row = current_row;
		col = current_col;
	}
};