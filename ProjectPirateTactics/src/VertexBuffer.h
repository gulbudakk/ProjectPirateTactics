#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const vector<vec3> data, unsigned int size);
	VertexBuffer(const vector<vec2> data, unsigned int size);
	VertexBuffer(const vector<float> data, unsigned int size);
	VertexBuffer() : m_RendererID(0) {}

	void Bind() const;
	void Unbind() const;
	inline unsigned int GetID() { return m_RendererID; };

	void Delete() const;
};

