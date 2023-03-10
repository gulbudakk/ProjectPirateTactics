#version 330 core

layout(location = 0) in vec3 position;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;
out vec3 fromLightVector;

uniform mat4 u_P;
uniform mat4 u_V;
uniform mat4 u_M;
uniform vec3 u_cameraPosition;
uniform vec3 u_lightPosition;

const float tiling = 1.0;

void main(void) {

	vec4 worldPosition = u_M * vec4(position.x, 0.0, position.z, 1.0);

	clipSpace = u_P * u_V * worldPosition;
	gl_Position = clipSpace;

	textureCoords = vec2(position.x / 2.0 + 0.5, position.z / 2.0 + 0.5) * tiling;
	toCameraVector = u_cameraPosition - worldPosition.xyz;
	fromLightVector = worldPosition.xyz - u_lightPosition;
}