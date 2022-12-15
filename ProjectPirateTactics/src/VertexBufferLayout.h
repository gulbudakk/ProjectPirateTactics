//taken from https://www.youtube.com/watch?v=oD1dvfbyf6A&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=14

#pragma once
#include <GL/glew.h>

#include <vector>
#include <iostream>

using namespace std;

struct VertexBufferElement {
	unsigned int vbID;
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		default:
			break;
		}
	}
};

class VertexBufferLayout {
private:
	vector<VertexBufferElement> m_elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0){}

	template<typename T>
	void Push(unsigned int vbID, unsigned int count) { /*static_assert(false);*/ }

	template<>
	void Push<float>(unsigned int vbID, unsigned int count) {
		m_elements.push_back({vbID, GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	inline const vector<VertexBufferElement> GetElements() const& { return m_elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};