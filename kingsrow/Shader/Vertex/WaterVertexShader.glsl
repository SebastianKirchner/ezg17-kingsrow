#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

out vec4 clipSpace;
out vec2 texCoords;

void main()
{
	clipSpace = MVP * vec4(position.x, position.y, position.z, 1.0);
	gl_Position = clipSpace;
	texCoords = vec2(position.x/2.0 + 0.5, position.y/2.0 + 0.5) * 6;
	
} 

