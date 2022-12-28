#pragma once

#include "../GameObject.h"
#include "Text.h"
#include "TextRenderer.h"

class TextObject : public GameObject {
private:
	TextRenderer m_textRenderer;

protected:
	Text& m_text;
	virtual void Update() = 0;

public:
	TextObject(Text& text, Shader& shader) : m_text(text), m_textRenderer(TextRenderer(text, shader)){}

	void Clear() { m_textRenderer.Clear(); }

	void Tick() {
		Update();

		m_textRenderer.Draw();
	}
};