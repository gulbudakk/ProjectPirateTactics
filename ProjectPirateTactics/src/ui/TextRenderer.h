#pragma once
#include "Text.h"
#include "../Shader.h"

class TextRenderer {
private:
	Text& m_text;
	Shader& m_shader;

public:
	TextRenderer(Text& text, Shader& shader) : m_text(text), m_shader(shader) {}

	void Draw();
	void Clear();
};