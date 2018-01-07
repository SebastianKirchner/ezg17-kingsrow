/**
 * This file is a part of a project from http://zompi.pl/light-shafts/
 * (c) 2014 Damian Nowakowski
 */

#version 330 core

in vec2 position;
in vec2 texCoord;
out vec2 inoutTexCoord;

void main()
{
	// Just pass the position and texture coordinates to the fragment shader.
	gl_Position = vec4(position,0,1);
    inoutTexCoord = texCoord;
}
