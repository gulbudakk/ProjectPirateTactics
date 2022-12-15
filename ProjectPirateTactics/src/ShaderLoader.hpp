#pragma once

#include <GL/glew.h>
#include <string>

using namespace std;

static GLuint CompileShader(GLuint type, const std::string& source);
GLuint LoadShaders(const string vertex_file_path,const string fragment_file_path);

