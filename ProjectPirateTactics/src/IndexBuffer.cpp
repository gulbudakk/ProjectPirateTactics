#include "IndexBuffer.h"

using namespace std;

IndexBuffer::IndexBuffer(const vector<unsigned int> data, unsigned int count)
    :m_Count(count) 
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
}

void IndexBuffer::Delete() const {

    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}