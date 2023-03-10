#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "GameObject.h"
#include "VisualGameObject.h"

class Tilemap : public GameObject
{
private:
	const unsigned int m_Rows;
	const unsigned int m_Cols;

	float m_Y;
	float m_CellSize;
	
	VisualGameObject*** m_World;
protected:
	void Tick(glm::vec4 clippingPlane);
	void Update(){}
public:
	Tilemap(unsigned int rows, unsigned int cols, float cellSize, float z);
	~Tilemap();

	void Draw(VisualGameObject& object, unsigned int row, unsigned int col);
	void Clear();
	void Clear(int row, int col);
	glm::vec3 ToWorldPoint(int x, int y);
	bool IsEmpty(int x, int y);
	bool IsValid(int row, int col);

	vector<vector<VisualGameObject*>*>* GetMap();
};

