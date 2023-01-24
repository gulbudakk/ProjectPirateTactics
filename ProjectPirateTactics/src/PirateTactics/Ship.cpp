#include "Ship.h"

#include "../Time.h"
#include <cmath>

void Ship::Update()
{
}

VisualGameObject& Ship::operator=(VisualGameObject& other)
{
	VisualGameObject::Swap(other);

	return *this;
}

bool Ship::MoveOnGrid(int row, int col)
{
	if (!m_obstacleTilemap.IsValid(current_row + row, current_col + col))
	{
		return false;
	}

	cout << "Set position." << endl;
	vec3 target = m_obstacleTilemap.ToWorldPoint(current_row + row, current_col + col);
	glm::vec3 dir = target - m_Transform.GetPosition();
	float angle = atan2(dir.z, dir.x) * 180 / 3.14;

	cout << angle << endl;

	vec3 rotation(m_Transform.GetRotation().x, -angle, m_Transform.GetRotation().z);

	m_Transform.SetRotation(rotation);
	m_Transform.SetPosition(target);


	current_row += row;
	current_col += col;

	return true;
}
