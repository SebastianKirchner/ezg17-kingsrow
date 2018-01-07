#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

//out vec4 clipSpace;

void main()
{
//	clipSpace = MVP * vec4(position.x, 0.0, position.y, 1.0);
	gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);

} 

