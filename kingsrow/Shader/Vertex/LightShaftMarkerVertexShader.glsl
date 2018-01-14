#version 330 core

in vec3 inPosition;
out vec4 geomPosition;

void main()
{
	geomPosition = vec4(inPosition, 1);
}
