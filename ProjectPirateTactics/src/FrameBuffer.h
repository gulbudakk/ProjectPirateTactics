#pragma once
#include "Texture.h"
#include "DepthBuffer.h"

class FrameBuffer
{
private:
	unsigned int m_RendererID;
	int m_Width, m_Height;

	Texture m_Texture;
	unsigned int m_DepthRendererID;

public:
	FrameBuffer(int width, int height, Texture deptTexture);
	FrameBuffer(int width, int height, DepthBuffer depthBuffer);

	void GenFrameBuffer();

	void Bind();
	void Unbind();

	Texture& GetTexture() {
		return m_Texture;
	}

	unsigned int GetDepthRendererID() {
		return m_DepthRendererID;
	}
};

