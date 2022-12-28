#version 330 core

in vec2 pass_textureCoords;

out vec4 color;

uniform vec3 u_color;
uniform sampler2D u_fontAtlas;

void main() {
	color = vec4(u_color, texture(u_fontAtlas, pass_textureCoords).a);
}