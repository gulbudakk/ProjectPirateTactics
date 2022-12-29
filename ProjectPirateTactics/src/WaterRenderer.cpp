#include "WaterRenderer.h"

void WaterRenderer::Draw()
{
	m_Shader.Bind();
	m_Shader.SetUniformMatrix4fv("u_V", 1, GL_FALSE, &m_Camera.GetView()[0][0]);
	m_Shader.SetUniformMatrix4fv("u_M", 1, GL_FALSE, &m_Transform.GetModel()[0][0]);
	m_Shader.SetUniformMatrix4fv("u_P", 1, GL_FALSE, &m_Camera.GetProjection()[0][0]);

	m_reflectionTexture.Bind(0);
	m_Shader.SetUniform1i("u_reflectionTexture", 0);

	m_refractionTexture.Bind(1);
	m_Shader.SetUniform1i("u_refractionTexture", 1);

	m_dudvTexture.Bind(2);
	m_Shader.SetUniform1i("u_dudvmap", 2);

	m_Shader.SetUniform1f("u_moveFactor", *m_moveFactor);

	vec3 cameraPosition = m_Camera.GetPosition();
	m_Shader.SetUniform3f("u_cameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);

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
