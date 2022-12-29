#include "Object3D.h"

using namespace std;
using namespace glm;

Object3D::Object3D(const char* path) {
	
	vector<glm::vec3> positions;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;

	loadOBJ(path, positions, uvs, normals);

	m_Va.Bind();

	CreateIndices(positions, uvs, normals, m_Indices, m_Positions, m_Uvs, m_Normals);

	VertexBuffer vb(m_Positions, m_Positions.size() * sizeof(vec3));
	VertexBuffer uvb(m_Uvs, m_Uvs.size() * sizeof(vec2));
	VertexBuffer nb(m_Normals, m_Normals.size() * sizeof(vec3));

	VertexBufferLayout layout;
	layout.Push<float>(vb.GetID(), 3);
	m_Va.AddBuffer(vb, layout);

	layout.Push<float>(uvb.GetID(), 2);
	m_Va.AddBuffer(uvb, layout);

	layout.Push<float>(nb.GetID(), 3);
	m_Va.AddBuffer(nb, layout);

	IndexBuffer ib(m_Indices, m_Indices.size());
	m_Ib = ib;
}

Object3D::Object3D(vector<vec3> positions) {

	m_Va.Bind();
	CreateIndices(positions, m_Positions, m_Indices);

	VertexBuffer vb(m_Positions, m_Positions.size() * sizeof(vec3));

	VertexBufferLayout layout;
	layout.Push<float>(vb.GetID(), 3);
	m_Va.AddBuffer(vb, layout);

	IndexBuffer ib(m_Indices, m_Indices.size());
	m_Ib = ib;
}


bool Object3D::loadOBJ(const char* path, vector<glm::vec3>& out_vertices, vector<glm::vec2>& out_uvs, vector<glm::vec3>& out_normals) {
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE* file;
	fopen_s(&file, path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, _countof(lineHeader));
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}
	fclose(file);
	return true;
}

bool Object3D::GetSimilarVertex(Vertex& packed, map<Vertex, unsigned int>& VertexToOutIndex, unsigned int& result) {
	std::map<Vertex, unsigned int>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}

void Object3D::CreateIndices(vector<vec3> in_positions, vector<vec2> in_uvs, vector<vec3> in_normals, vector<unsigned int>& out_indices, vector<vec3>& out_positions, vector<vec2>& out_uvs, vector<vec3>& out_normals) {

	map<Vertex, unsigned int> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i < in_positions.size(); i++) {

		Vertex packed = { in_positions[i], in_uvs[i], in_normals[i] };

		// Try to find a similar vertex in out_XXXX
		unsigned int index;
		bool found = GetSimilarVertex(packed, VertexToOutIndex, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_positions.push_back(in_positions[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);

			unsigned short newindex = (unsigned int)out_positions.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

void Object3D::CreateIndices(vector<vec3> in_positions, vector<vec3>& out_positions, vector<unsigned int>& out_indices) {

	for (unsigned int i = 0; i < in_positions.size(); i++)
	{
		// Try to find a similar vertex in out_XXXX
		unsigned int index;
		bool found = GetSimilarVertex(out_positions, in_positions[i], index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_positions.push_back(in_positions[i]);
			unsigned int newindex = (unsigned int)out_positions.size() - 1;
			out_indices.push_back(newindex);
		}
	}
}

bool Object3D::GetSimilarVertex(vector<vec3> in_positions, vec3 vertex, unsigned int& result) {

	// Lame linear search
	for (unsigned int i = 0; i < in_positions.size(); i++) {
		if (in_positions[i].x == vertex.x && in_positions[i].y == vertex.y && in_positions[i].z == vertex.z) {
			result = i;
			return true;
		}
	}
	// No other vertex could be used instead.
	// Looks like we'll have to add it to the VBO.
	return false;
}
