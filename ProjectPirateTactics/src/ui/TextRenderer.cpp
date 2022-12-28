#include "TextRenderer.h"

void TextRenderer::Draw() {

	Application::Enable(GL_BLEND);
	Application::SetBlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Application::Disable(GL_DEPTH_TEST);

 	m_shader.Bind();

	m_shader.SetUniform2f("u_translation", m_text.GetTranslation().x, m_text.GetTranslation().y);

	m_shader.SetUniform3f("u_color", m_text.GetColor().x, m_text.GetColor().y, m_text.GetColor().z);

	m_text.GetFont().GetTexture().Bind();
	m_shader.SetUniform1i("u_fontAtlas", 0);
	
	VertexArray& va = m_text.GetVertexArray();
	va.Bind();

	glDrawArrays(GL_TRIANGLES, 0, m_text.GetVertexCount());

	Application::Enable(GL_DEPTH_TEST);
	Application::Disable(GL_BLEND);
}

void TextRenderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}