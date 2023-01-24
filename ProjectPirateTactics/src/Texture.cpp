#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const string path, int wrapType, int type) : m_FilePath(path) {

	m_type = type;
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(type, m_RendererID);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapType);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapType);
	glTexParameteri(type, GL_TEXTURE_WRAP_R, wrapType);
	
	glTexParameterf(type, GL_TEXTURE_LOD_BIAS, 0);

	glTexImage2D(type, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

	glTexImage2D(type, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

	Unbind();

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::Texture(int width, int height, unsigned char* buffer, GLint format) {
	m_LocalBuffer = buffer;
	m_Width = width;
	m_Height = height;
	m_type = GL_TEXTURE_2D;

	glGenTextures(1, &m_RendererID);
	glBindTexture(m_type, m_RendererID);
	glTexImage2D(m_type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);
	glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	Unbind();
}

void Texture::Bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_type, m_RendererID);
}

void Texture::Unbind() const {
	glBindTexture(m_type, 0);
}


void Texture::Delete() const {
	glDeleteTextures(m_type, &m_RendererID);
}