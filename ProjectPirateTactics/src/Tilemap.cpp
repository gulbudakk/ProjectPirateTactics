#include "Tilemap.h"

#include <iostream>

Tilemap::Tilemap(const unsigned int rows, const unsigned int cols, float cellSize) : m_Rows(rows), m_Cols(cols), m_CellSize(cellSize){
	m_World = (VisualGameObject ***) malloc(m_Rows * sizeof(VisualGameObject**));

	for (unsigned int r = 0; r < m_Rows; r++)
	{
		m_World[r] = (VisualGameObject**)malloc(m_Cols * sizeof(VisualGameObject*));

		for (unsigned int c = 0; c < m_Cols; c++)
		{
			m_World[r][c] = nullptr;
		}

	}

}

Tilemap::~Tilemap() {
	for (unsigned int i = 0; i < m_Rows; i++)
	{
		free(m_World[i]);
	}

	free(m_World);
}

void Tilemap::Update() {

	for (unsigned int r = 0; r < m_Rows; r++)
	{
		for (unsigned int c = 0; c < m_Cols; c++)
		{
			if (m_World[r][c] != nullptr)
			{
				m_World[r][c]->Tick();
			}
		}
	}
}

void Tilemap::Clear() {

	for (unsigned int r = 0; r < m_Rows; r++)
	{
		for (unsigned int c = 0; c < m_Cols; c++)
		{
			if (m_World[r][c] != nullptr)
			{
				m_World[r][c]->Clear();
			}
		}
	}
}

void Tilemap::Draw(VisualGameObject& object, unsigned int row, unsigned int col) {
	m_World[row][col] = &object;

	object.GetTransform().SetModel(glm::translate(glm::mat4(1.0f), glm::vec3(row * m_CellSize, 0, col * m_CellSize)));
}

