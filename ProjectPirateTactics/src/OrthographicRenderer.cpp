#include "OrthographicRenderer.h"
#include "Camera.h"
#include "Object3D.h"

using namespace glm;

void OrthographicRenderer::Draw(glm::vec4 clippingPlane) {

	m_Shader.Bind();
	m_Texture.Bind();
	m_Shader.SetUniform1i("u_Texture", 0);

	m_Shader.SetUniformMatrix4fv("u_Model", 1, GL_FALSE, &m_Transform.GetModel()[0][0]);

	VertexArray& va = m_Object.GetVertexArray();
	va.Bind();

	IndexBuffer& ib = m_Object.GetIndexBuffer();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OrthographicRenderer::Clear() const {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}