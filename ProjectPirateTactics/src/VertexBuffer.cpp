#include "VertexBuffer.h"

using namespace std;
using namespace glm;

VertexBuffer::VertexBuffer(const vector<vec3> data, unsigned int size) {

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, &data[0], GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const vector<vec2> data, unsigned int size) {

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, &data[0], GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const vector<float> data, unsigned int size) {

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, &data[0], GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const {

    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const {

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete() const {
    glDeleteBuffers(1, &m_RendererID);
}
