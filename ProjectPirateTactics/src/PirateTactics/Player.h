#pragma once
#include "Ship.h"
#include "HealthText.h"

class Player {

private:
	Ship& m_ship;
	HealthText& m_health;

public:
	Player(Ship& ship, HealthText health) : m_ship(ship), m_health(health){}

	Ship& GetShip() { return m_ship; }
	HealthText& GetHealth() { return m_health; }
};