#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

#include <map>
#include <vector>

using namespace glm;
using namespace std;

struct Vertex {
	vec3 position;
	vec2 uv;
	//vec3 normal;

	bool operator<(const Vertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(Vertex)) > 0;
	};
};

class Object3D
{
private:
	VertexBuffer m_Vb;
	VertexBuffer m_Cb;

	VertexArray m_Va;
	IndexBuffer m_Ib;
	Shader& m_Shader;

	vector<Vertex> m_Vertices;
	vector<vec3> m_Positions;
	vector<vec2> m_Uvs;
	vector<unsigned int> m_Indices;

	bool GetSimilarVertex(vec3 vertex, unsigned int& result);
	bool GetSimilarVertex(Vertex& packed, map<Vertex, unsigned int>& VertexToOutIndex, unsigned int& result);
	bool loadOBJ(const char* path, vector<glm::vec3>& out_vertices, vector<glm::vec2>& out_uvs, vector<glm::vec3>& out_normals);
	void CreateIndices(vector<vec3> positions);
	void CreateIndices(vector<vec3> positions, vector<vec2> uvs);

public:
	Object3D(const char* path, Shader& shader);
	Shader& GetShader() { return m_Shader; }
	VertexArray& GetVertexArray() { return m_Va; }
	IndexBuffer& GetIndexBuffer() { return m_Ib; }
};

