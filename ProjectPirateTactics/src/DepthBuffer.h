#pragma once

#include "GL/glew.h"

class DepthBuffer
{
private:
	unsigned int m_RendererID;

public:
	DepthBuffer(int width, int height);

	void Bind();
	void Unbind();

	unsigned int GetID() {
		return m_RendererID;
	}
};

