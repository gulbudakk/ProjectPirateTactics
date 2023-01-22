#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 u_Model;

void main() {

	vec3 worldspace = (u_Model * vec4(position, 1)).xyz;
	gl_Position = vec4(worldspace.xy, 0.0, 1.0);

	UV = vertexUV;
}