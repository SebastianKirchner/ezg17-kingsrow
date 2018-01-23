#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 M;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform vec3 cameraPos;
uniform vec3 lightPos;

out vec4 clipSpace;
out vec2 texCoords;
out vec3 camDirection;
out vec3 lightRayVec;

void main()
{
	clipSpace = MVP * vec4(position.x, position.y, position.z, 1.0);
	gl_Position = clipSpace;
	texCoords = vec2(position.x/2.0 + 0.5, position.z/2.0 + 0.5) * 2;

	vec4 worldPosition = M * vec4(position.x, 0.0, position.y, 1.0);	
	camDirection = cameraPos - worldPosition.xyz;
	lightRayVec = worldPosition.xyz - lightPos;
} 

