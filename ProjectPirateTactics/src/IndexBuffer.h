#pragma once
#include <GL/glew.h>
#include <vector>

using namespace std;

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const vector<unsigned int> data, unsigned int count);
	IndexBuffer(){}

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

	void Delete() const;
};

