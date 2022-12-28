#pragma once

#include "../ui/TextObject.h"

class ScoreText : public TextObject
{

protected:
	void Update();

public:
	ScoreText(Text& text, Shader& shader) : TextObject(text, shader) {}

	void SetPosition(vec2 newPosition);
};

