#include "Renderer.h"
#include "Camera.h"
#include "Object3D.h"

void Renderer::Draw() {
	
	m_Shader.Bind();
	m_Shader.SetUniformMatrix4fv("u_MVP", 1, GL_FALSE, &m_Camera.GetMVP(m_Transform.GetModel())[0][0]);

	m_Texture.Bind();
	m_Shader.SetUniform1i("u_Texture", 0);
	m_Shader.SetUniformMatrix4fv("u_V", 1, GL_FALSE, &m_Camera.GetView()[0][0]);
	m_Shader.SetUniformMatrix4fv("u_M", 1, GL_FALSE, &m_Transform.GetModel()[0][0]);


	glm::vec3 lightPos = glm::vec3(8, 8, 8);
	m_Shader.SetUniform3f("u_LightPosition", lightPos.x, lightPos.y, lightPos.z);

	IndexBuffer& ib = m_Object.GetIndexBuffer();
	ib.Bind();

	VertexArray& va = m_Object.GetVertexArray();
	va.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles
	
	/*
	Shader shader = m_Object.GetShader();

	shader.Bind();
	shader.SetUniform4fv("u_MVP", 1, GL_FALSE, &m_Camera.GetMVP(m_Model)[0][0]);

	VertexArray& va = m_Object.GetVertexArray();
	va.Bind();

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	*/
}



void Renderer::Clear() const {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}