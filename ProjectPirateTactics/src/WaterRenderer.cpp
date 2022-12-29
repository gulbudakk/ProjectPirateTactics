#include "WaterRenderer.h"

void WaterRenderer::Draw()
{
	m_Shader.Bind();
	m_Shader.SetUniformMatrix4fv("u_V", 1, GL_FALSE, &m_Camera.GetView()[0][0]);
	m_Shader.SetUniformMatrix4fv("u_M", 1, GL_FALSE, &m_Transform.GetModel()[0][0]);
	m_Shader.SetUniformMatrix4fv("u_P", 1, GL_FALSE, &m_Camera.GetProjection()[0][0]);

	VertexArray& va = m_Object.GetVertexArray();
	va.Bind();

	IndexBuffer& ib = m_Object.GetIndexBuffer();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void WaterRenderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
