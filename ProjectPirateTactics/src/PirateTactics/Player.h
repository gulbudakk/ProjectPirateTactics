#pragma once
#include "Ship.h"

class Player {

private:
	Ship& m_ship;

public:
	Player(Ship& ship) : m_ship(ship){}

	Ship& GetShip() { return m_ship; }
};