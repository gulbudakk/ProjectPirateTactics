#pragma once

#include <string>
#include <unordered_map>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

using namespace std;

class Shader
{
private:
	unsigned int m_RendererID;
	unordered_map<string, int> m_UniformLocationCache;

	int GetUniformLocation(const string& name);
	unsigned int CompileShader(unsigned int type, const string& source);
	unsigned int LoadShaders(const string vertex_file_path, const string fragment_file_path);
	
public:

	Shader(const string vertexShaderFilePath, const string fragmentShaderFilepath);

	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const string& name, float v0, float v1, float v2, float v3);
	void SetUniformMatrix4fv(const string& name, unsigned int count, bool transpose, const float* value);
	void SetUniform1i(const string& name, int value);
};

