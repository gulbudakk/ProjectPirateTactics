#pragma once

#include "../GameObject.h"
#include "Text.h"
#include "TextRenderer.h"

class TextObject : public GameObject {
private:
	Text& m_text;
	TextRenderer& m_textRenderer;
};