#version 330 core

in vec3 fragmentColor;
// Output data
out vec3 color;

void main()
{

	// Output color = red 
	color = fragmentColor;
	//color = vec3(1, 0, 0);

}
