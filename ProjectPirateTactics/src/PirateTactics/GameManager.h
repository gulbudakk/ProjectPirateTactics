#pragma once

#include <vector>

#include "Player.h"
#include "Heart.h"

class GameManager
{
private:
	Player& m_player;
	Tilemap& m_Obstacles;
	bool m_isMovingActive = true;

public:
	GameManager(Player& player, Tilemap& obstacleTilemap) : m_player(player), m_Obstacles(obstacleTilemap) {}
	void Tick();
	void TryMoveShip();
	void TryDamagePlayer();
	void MoveObstacles();
};

