#include "Tilemap.h"

#include <iostream>

Tilemap::Tilemap(const unsigned int rows, const unsigned int cols, float cellSize, float z) : m_Rows(rows), m_Cols(cols), m_CellSize(cellSize), m_Y(z){
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

void Tilemap::Tick(glm::vec4 clippingPlane) {

	for (unsigned int r = 0; r < m_Rows; r++)
	{
		for (unsigned int c = 0; c < m_Cols; c++)
		{
			if (m_World[r][c] != nullptr)
			{
				m_World[r][c]->Tick(clippingPlane);
			}
		}
	}

	Update();
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

	if (m_World[row][col] != nullptr)
	{
		std::cout << "Warning: Drawing an occupied cell!" << std::endl;
	}

	m_World[row][col] = &object;

	object.GetTransform().SetPosition(glm::vec3(row * m_CellSize, m_Y * m_CellSize, col * m_CellSize));
}

