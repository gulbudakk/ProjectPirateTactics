#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

#include <map>

#include <map>
#include <vector>

using namespace glm;
using namespace std;

struct Vertex {
	vec3 position;
	vec2 uv;
	vec3 normal;

	bool operator<(const Vertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(Vertex)) > 0;
	};
};

class Object3D
{
private:
	VertexBuffer m_Vb;

	VertexArray m_Va;
	IndexBuffer m_Ib;


	vector<Vertex> m_Vertices;
	vector<vec3> m_Positions;
	vector<vec2> m_Uvs;
	vector<vec3> m_Normals;
	vector<unsigned int> m_Indices;

	bool loadOBJ(const char* path, vector<glm::vec3>& out_vertices, vector<glm::vec2>& out_uvs, vector<glm::vec3>& out_normals);
	void CreateIndices(vector<vec3> in_positions, vector<vec2> in_uvs, vector<vec3> in_normals, vector<unsigned int>& out_indices, vector<vec3>& out_positions, vector<vec2>& out_uvs, vector<vec3>& out_normals);
	bool GetSimilarVertex(Vertex& packed, map<Vertex, unsigned int>& VertexToOutIndex, unsigned int& result);

public:
	Object3D(const char* path);
	VertexArray& GetVertexArray() { return m_Va; }
	IndexBuffer& GetIndexBuffer() { return m_Ib; }
};

