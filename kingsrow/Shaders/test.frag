#version 330 core

in vec3 outColor;
in vec3 outPosition;
out vec4 color;

uniform float colorAdapter;

void main()
{
   //color = vec4(outColor.x * colorAdapter, 1- (outColor.y*colorAdapter), outColor.z * colorAdapter,  0.7f);
   color = vec4(outPosition, 1.0f);
}