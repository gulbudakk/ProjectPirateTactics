#include "Renderer.h"
#include "Camera.h"
#include "Object3D.h"

using namespace glm;

Light Renderer::m_Light(vec3(0.9f, 1, 0.9f), vec3(6.12, 10.1, 6.12), 80.0f);

void Renderer::Draw(glm::vec4 clippingPlane) {
	
	m_Shader.Bind();
	m_Shader.SetUniformMatrix4fv("u_MVP", 1, GL_FALSE, &m_Camera.GetMVP(m_Transform.GetModel())[0][0]);

	m_Shader.SetUniform4f("u_ClippingPlane", clippingPlane.x, clippingPlane.y, clippingPlane.z, clippingPlane.w);

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

	VertexArray& va = m_Object.GetVertexArray();
	va.Bind();

	IndexBuffer& ib = m_Object.GetIndexBuffer();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}



void Renderer::Clear() const {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}