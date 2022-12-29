#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(int width, int height)
{
	glGenRenderbuffers(1, &m_RendererID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,
		height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, m_RendererID);

	Unbind();
}

void DepthBuffer::Bind()
{
	glBindRenderbuffer(1, m_RendererID);
}

void DepthBuffer::Unbind()
{
	glBindRenderbuffer(1, 0);
}
