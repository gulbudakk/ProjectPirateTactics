#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 position;

// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 1) in vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;

// Values that stay constant for the whole mesh.
uniform mat4 u_MVP;

void main(){

	gl_Position = u_MVP * position;

	fragmentColor = vertexColor;
}