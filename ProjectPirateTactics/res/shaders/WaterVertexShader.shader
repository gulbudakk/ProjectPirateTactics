#version 330 core

layout(location = 0) in vec3 position;

out vec2 textureCoords;

uniform mat4 u_P;
uniform mat4 u_V;
uniform mat4 u_M;


void main(void) {

	gl_Position = u_P * u_V * u_M * vec4(position.x, 0.0, position.z, 1.0);
	textureCoords = vec2(position.x / 2.0 + 0.5, position.z / 2.0 + 0.5);

}