#include "FrameBuffer.h"
#include "Application.h"

FrameBuffer::FrameBuffer(int width, int height, Texture depthTexture) : m_Width(width), m_Height(height), m_Texture(Texture(width, height, NULL, GL_RGB))
{
	GenFrameBuffer();

	m_Texture.Bind();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_Texture.GetID(), 0);

	m_DepthRendererID = depthTexture.GetID();
	//depthTexture.Bind();
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_DepthRendererID, 0);
}

FrameBuffer::FrameBuffer(int width, int height, DepthBuffer depthBuffer) : m_Width(width), m_Height(height), m_Texture(Texture(width, height, NULL, GL_RGB))
{
	GenFrameBuffer();

	m_Texture.Bind();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_Texture.GetID(), 0);

	m_DepthRendererID = depthBuffer.GetID();
	depthBuffer.Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRendererID);
}

void FrameBuffer::GenFrameBuffer() 
{
	glGenFramebuffers(1, &m_RendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void FrameBuffer::Bind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	glViewport(0, 0, m_Width, m_Height);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Application::GetWidth(), Application::GetHeight());
}
