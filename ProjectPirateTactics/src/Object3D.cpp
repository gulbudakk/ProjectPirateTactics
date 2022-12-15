#include "Object3D.h"

using namespace std;

Object3D::Object3D(const char* path, Shader& shader) : m_Shader(shader){
	
	vector<glm::vec3> out_normals;

	loadOBJ(path, m_Positions, m_Uvs, out_normals);

	m_Va.Bind();

	CreateIndices(m_Positions, m_Uvs);

	VertexBuffer vb(m_Positions, m_Positions.size() * sizeof(vec3));
	VertexBuffer uvb(m_Uvs, m_Uvs.size() * sizeof(vec2));

	VertexBufferLayout layout;
	layout.Push<float>(vb.GetID(), 3);
	m_Va.AddBuffer(vb, layout);

	layout.Push<float>(uvb.GetID(), 2);
	m_Va.AddBuffer(uvb, layout);

	IndexBuffer ib(m_Indices, m_Indices.size());
	m_Ib = ib;

	/*
	static const float g_vertex_buffer_data[] = {
-1.0f,-1.0f,-1.0f, // triangle 1 : begin
-1.0f,-1.0f, 1.0f,
-1.0f, 1.0f, 1.0f, // triangle 1 : end
1.0f, 1.0f,-1.0f, // triangle 2 : begin
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f,-1.0f, // triangle 2 : end
1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,
1.0f,-1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
1.0f,-1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f, 1.0f,
1.0f,-1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f,-1.0f,
-1.0f, 1.0f,-1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,
1.0f,-1.0f, 1.0f
	};
	static const float g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
	};

	m_Va.Bind();

	VertexBuffer vb(g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
	VertexBuffer cb(g_color_buffer_data, sizeof(g_color_buffer_data));

	VertexBufferLayout layout;
	layout.Push<float>(vb.GetID(), 3);
	m_Va.AddBuffer(vb, layout);

	layout.Push<float>(cb.GetID(), 3);
	m_Va.AddBuffer(cb, layout);
	*/
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

void Object3D::CreateIndices(vector<vec3> positions) {

	for (unsigned int i = 0; i < positions.size(); i++)
	{
		// Try to find a similar vertex in out_XXXX
		unsigned int index;
		bool found = GetSimilarVertex(positions[i], index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			m_Indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			m_Positions.push_back(positions[i]);
			unsigned int newindex = (unsigned int)m_Positions.size() - 1;
			m_Indices.push_back(newindex);
		}
	}
}

void Object3D::CreateIndices(vector<vec3> positions, vector<vec2> uvs) {

	map<Vertex, unsigned int> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i < positions.size(); i++) {

		Vertex packed = { positions[i], uvs[i]};

		// Try to find a similar vertex in out_XXXX
		unsigned int index;
		bool found = GetSimilarVertex(packed, VertexToOutIndex, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			m_Indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			m_Positions.push_back(positions[i]);
			m_Uvs.push_back(uvs[i]);
			unsigned short newindex = (unsigned int)m_Positions.size() - 1;
			m_Indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

bool Object3D::GetSimilarVertex(vec3 vertex, unsigned int& result) {
	
	// Lame linear search
	for (unsigned int i = 0; i < m_Positions.size(); i++) {
		if (m_Positions[i].x == vertex.x && m_Positions[i].y == vertex.y && m_Positions[i].z == vertex.z) {
			result = i;
			return true;
		}
	}
	// No other vertex could be used instead.
	// Looks like we'll have to add it to the VBO.
	return false;
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


