#include "Heart.h"
#include "../Time.h"

void Heart::Update()
{
	vec3 rotation = m_Transform.GetRotation();

	m_Transform.SetRotation(vec3(rotation.x, rotation.y + speed * Time::GetDeltaTime(), rotation.z));
}
