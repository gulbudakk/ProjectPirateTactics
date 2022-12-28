#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoords;

out vec2 pass_textureCoords;

uniform vec2 u_translation;

void main() {
	gl_Position = vec4(position + u_translation, 0.0, 1.0);

	pass_textureCoords = textureCoords;
}