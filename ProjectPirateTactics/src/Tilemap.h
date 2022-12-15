#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "GameObject.h"
#include "VisualGameObject.h"

class Tilemap : public GameObject
{
private:
	const unsigned int m_Rows;
	const unsigned int m_Cols;

	float m_CellSize;
	
	VisualGameObject*** m_World;
protected:
	void Update();
public:
	Tilemap(unsigned int rows, unsigned int cols, float cellSize);
	~Tilemap();

	void Draw(VisualGameObject& object, unsigned int row, unsigned int col);
	void Clear();
};

