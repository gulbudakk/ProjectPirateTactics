#version 330 core

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;

out vec4 out_Color;

uniform sampler2D u_reflectionTexture;
uniform sampler2D u_refractionTexture;
uniform sampler2D u_dudvmap;

uniform float u_moveFactor;

const float waveStrength = 0.03;

void main(void) {

	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

	vec2 distortion1 = (texture(u_dudvmap, vec2(textureCoords.x + u_moveFactor, textureCoords.y)).rg * 2.0 - 1.0) * waveStrength;
	vec2 distortion2 = (texture(u_dudvmap, vec2(-textureCoords.x + u_moveFactor, textureCoords.y + u_moveFactor)).rg * 2.0 - 1.0) * waveStrength;
	vec2 distortion = distortion1 + distortion2;

	refractTexCoords += distortion;
	refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);

	reflectTexCoords += distortion;
	reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
	reflectTexCoords.y = clamp(reflectTexCoords.y, -0.001, -0.999);

	vec4 reflectColor = texture(u_reflectionTexture, reflectTexCoords);
	vec4 refractColor = texture(u_refractionTexture, refractTexCoords);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = dot(viewVector, vec3(0.0, 1.0, 0.0));
	refractiveFactor = pow(refractiveFactor, 2);

	out_Color = mix(reflectColor, refractColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0.0, 0.3, 0.5, 0.1), 0.2);
}