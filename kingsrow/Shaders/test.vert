#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform float colorAdapter;
uniform float offset;

out vec3 outColor;
out vec3 outPosition;
void main()
{
   gl_Position = vec4(position.x * -1.0f + offset, position.y * -1.0f + offset, position.z * -1.0f + offset, 1.0);
   outColor = color;
   outPosition = gl_Position.xyz;
}