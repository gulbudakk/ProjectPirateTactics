#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D u_Texture;

void main() {
	color = vec4(texture(u_Texture, UV));
}