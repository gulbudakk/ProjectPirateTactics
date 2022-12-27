#include "Renderer.h"
#include "Camera.h"
#include "Object3D.h"

using namespace glm;

const Light Renderer::m_Light(vec3(0.9f, 1, 0.9f), vec3(1, 10, 1), 50.0f);

void Renderer::Draw() {
	
	m_Shader.Bind();
	m_Shader.SetUniformMatrix4fv("u_MVP", 1, GL_FALSE, &m_Camera.GetMVP(m_Transform.GetModel())[0][0]);

	m_Texture.Bind();
	m_Shader.SetUniform1i("u_Texture", 0);
	m_Shader.SetUniformMatrix4fv("u_V", 1, GL_FALSE, &m_Camera.GetView()[0][0]);
	m_Shader.SetUniformMatrix4fv("u_M", 1, GL_FALSE, &m_Transform.GetModel()[0][0]);

	vec3 lightPosition = m_Light.GetPosition();
	m_Shader.SetUniform3f("u_LightPosition", lightPosition.x, lightPosition.y, lightPosition.z);

	vec3 lightColor = m_Light.GetColor();
	m_Shader.SetUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);

	float lightPower = m_Light.GetPower();
	m_Shader.SetUniform1f("u_LightPower", lightPower);

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