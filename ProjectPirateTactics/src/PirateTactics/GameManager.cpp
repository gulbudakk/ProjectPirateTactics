#include "GameManager.h"
#include "../Input.h"
#include "../Time.h"

void GameManager::Tick() {

	TryMoveShip();
	//MoveObstacles();
}

void GameManager::TryMoveShip() {
	if (Input::GetMouseButton(MouseCode::Button1))
	{
		return;
	}

	if (Input::GetKey(KeyCode::A) == GLFW_RELEASE && 
		Input::GetKey(KeyCode::D) == GLFW_RELEASE && 
		Input::GetKey(KeyCode::W) == GLFW_RELEASE && 
		Input::GetKey(KeyCode::S) == GLFW_RELEASE)
	{
		m_isMovingActive = true;
	}

	if (!m_isMovingActive)
	{
		return;
	}

	if (Input::GetKey(KeyCode::A) == GLFW_PRESS)
	{
		m_player.GetShip().MoveOnGrid(0, -1);
		m_isMovingActive = false;
	}
	if (Input::GetKey(KeyCode::D) == GLFW_PRESS)
	{
		m_player.GetShip().MoveOnGrid(0, 1);
		m_isMovingActive = false;
	}

	if (Input::GetKey(KeyCode::W) == GLFW_PRESS)
	{
		m_player.GetShip().MoveOnGrid(1, 0);
		m_isMovingActive = false;
	}

	if (Input::GetKey(KeyCode::S) == GLFW_PRESS)
	{
		m_player.GetShip().MoveOnGrid(-1, 0);
		m_isMovingActive = false;
	}
}

void GameManager::MoveObstacles() {

	vector<vector<VisualGameObject*>*>* oldMap = m_Obstacles.GetMap();

	m_Obstacles.Clear();

	for (unsigned int i = 1; i < oldMap->size(); i++)
	{
		for (unsigned int k = 0; k < (*oldMap)[i]->size(); k++)
		{
			if ((*(*oldMap)[i])[k] == nullptr)
			{
				continue;
			}

			VisualGameObject* newObject = new VisualGameObject(*(*(*oldMap)[i])[k]);
			m_Obstacles.Draw(*newObject, i - 1, k);
		}
	}

	for (unsigned int i = 0; i < (*oldMap)[oldMap->size()-1]->size(); i++)
	{
		if ((*(*oldMap)[oldMap->size() - 1])[i] == nullptr)
		{
			continue;
		}

		VisualGameObject* newObject = new VisualGameObject(*(*(*oldMap)[oldMap->size() - 1])[i]);
		m_Obstacles.Draw(*newObject, oldMap->size() - 1, i);
	}
}