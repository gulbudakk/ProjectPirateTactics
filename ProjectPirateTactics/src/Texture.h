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

	int m_Width, m_Height, m_BPP = 0;

public:
	Texture(const string path, int wrapType = GL_CLAMP);
	Texture(int width, int height, unsigned char* buffer, GLint format);

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void Delete() const;

	unsigned int GetID() {
		return m_RendererID;
	}
};

