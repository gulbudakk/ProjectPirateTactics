#pragma once

#include "../ui/TextObject.h"

class HealthText : public TextObject
{

protected:
	void Update();

	int currentHealt = 3;
	int maxHealt = 3;
public:
	HealthText(Text& text, Shader& shader) : TextObject(text, shader) {}

	void SetPosition(vec2 newPosition);

	void TakeDamage(int damage) {
		currentHealt -= damage;
		m_text.SetText(to_string(currentHealt));
	}

	int GetCurrentHealth() {
		return currentHealt;
	}
};

