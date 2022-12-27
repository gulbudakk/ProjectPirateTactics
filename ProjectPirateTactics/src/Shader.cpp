#include "Shader.h"

#include <iostream>

Shader::Shader(const string vertexShaderFilePath, const string fragmentShaderFilepath) {
	m_RendererID = LoadShaders(vertexShaderFilePath, fragmentShaderFilepath);
}

Shader::~Shader() {
	glDeleteProgram(m_RendererID);
}

unsigned int Shader::CompileShader(unsigned int type, const string& source) {
	// Create the shader
	GLuint id = glCreateShader(type);

	// Compile Shader
	char const* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int result;
	int length;
	// Check Shader
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
	if (length > 0) {
		std::vector<char> errorMessage(length + 1);
		glGetShaderInfoLog(id, length, NULL, &errorMessage[0]);
		printf("%s\n", &errorMessage[0]);
	}

	return id;
}

unsigned int Shader::LoadShaders(const string vertex_file_path, const string fragment_file_path)
{
	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Create the shaders
	GLuint VertexShaderID = Shader::CompileShader(GL_VERTEX_SHADER, VertexShaderCode);
	GLuint FragmentShaderID = Shader::CompileShader(GL_FRAGMENT_SHADER, FragmentShaderCode);

	// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

int Shader::GetUniformLocation(const string& name) {

	//auto var = glGetUniformLocation(m_RendererID, name.c_str());;
	//return var;

	if (m_UniformLocationCache.size() <= 0 && m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	
	int location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location <= -1)
	{
		cout << "Warning: uniform '" << name << "' doesn't exist!" << endl;
	}
	else
	{
		m_UniformLocationCache[name] = location;
	}

	return location;
}

void Shader::Bind() const {
	glUseProgram(m_RendererID);
}
void Shader::Unbind() const {
	glUseProgram(0);
}

void Shader::SetUniform4f(const string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform3f(const string& name, float v0, float v1, float v2) {
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniformMatrix4fv(const string& name, unsigned int count, bool transpose, const float* value) {
	glUniformMatrix4fv(GetUniformLocation(name), count, transpose, value);
}

void Shader::SetUniform1i(const string& name, int value) {
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const string& name, float value) {
	glUniform1f(GetUniformLocation(name), value);
}