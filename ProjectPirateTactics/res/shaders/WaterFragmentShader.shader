#version 330 core

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D u_reflectionTexture;
uniform sampler2D u_refractionTexture;

void main(void) {

	vec4 reflectColor = texture(u_reflectionTexture, textureCoords);
	vec4 refractColor = texture(u_refractionTexture, textureCoords);

	out_Color = mix(reflectColor, refractColor, 0.5);
}