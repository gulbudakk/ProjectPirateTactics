#pragma once
#include <GL/glew.h>
#include <string>

using namespace std;

class Texture
{
private:
	unsigned int m_RendererID;
	string m_FilePath;
	unsigned char* m_LocalBuffer;

	int m_Width, m_Height, m_BPP;

public:
	Texture(const string path, int wrapType = GL_CLAMP);

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void Delete() const;
};

