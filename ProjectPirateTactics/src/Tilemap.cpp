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

vec3 Tilemap::ToWorldPoint(int row, int col)
{

	return glm::vec3(row * m_CellSize, m_Y * m_CellSize, col * m_CellSize);
}

bool Tilemap::IsEmpty(int row, int col)
{
	if (IsValid(row, col) && m_World[row][col] == nullptr)
	{
		return false;
	}

	return true;
}

bool Tilemap::IsValid(int row, int col) {
	if (row >= m_Rows || row < 0 || col >= m_Cols || col < 0)
	{
		return false;
	}

	return true;
}

vector<vector<VisualGameObject*>*>* Tilemap::GetMap()
{
	vector<vector<VisualGameObject*>*>* map = new vector<vector<VisualGameObject*>*>();

	for (unsigned int r = 0; r < m_Rows; r++)
	{
		vector<VisualGameObject*>* row = new vector<VisualGameObject*>();
		for (unsigned int c = 0; c < m_Cols; c++)
		{
			if (m_World[r][c] == nullptr)
			{
				row->push_back(nullptr);
				continue;
			}

			VisualGameObject* copy = new VisualGameObject(*m_World[r][c]);
			row->push_back(copy);
		}


		map->push_back(new vector<VisualGameObject*>(*row));
	}

	return map;
}

void Tilemap::Draw(VisualGameObject& object, unsigned int row, unsigned int col) {

	if (!IsValid(row, col))
	{
		std::cout << "Warning: Cell is off the grid." << std::endl;
		return;
	}

	if (m_World[row][col] != nullptr)
	{
		std::cout << "Warning: Drawing an occupied cell!" << std::endl;
	}

	m_World[row][col] = &object;
	
	if (&object == nullptr)
	{
		return;
	}

	object.GetTransform().SetPosition(glm::vec3(row * m_CellSize, m_Y * m_CellSize, col * m_CellSize));
}

