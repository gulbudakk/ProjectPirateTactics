#version 330 core

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;
in vec3 fromLightVector;

out vec4 out_Color;

uniform sampler2D u_reflectionTexture;
uniform sampler2D u_refractionTexture;
uniform sampler2D u_dudvmap;
uniform sampler2D u_normalmap;

uniform float u_moveFactor;

uniform vec3 u_lightColor;

const float waveStrength = 0.03;
const float shineDamper = 20.0;
const float reflectivity = 0.6;

void main(void) {

	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

	vec2 distortedTexCoords = texture(u_dudvmap, vec2(textureCoords.x + u_moveFactor, textureCoords.y)).rg * 0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y + u_moveFactor);
	vec2 distortion = (texture(u_dudvmap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;

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

	vec4 normalMapColor = texture(u_normalmap, distortedTexCoords);
	vec3 normal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b, normalMapColor.g * 2.0 - 1.0);
	normal = normalize(normal);

	vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
	float specular = max(dot(reflectedLight, viewVector), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = u_lightColor * specular * reflectivity;

	out_Color = mix(reflectColor, refractColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0.0, 0.3, 0.5, 0.1), 0.2) + vec4(specularHighlights, 0.0);
}