#version 330

// One point generates trangle_strip with 41 vertices (it will be a circle)
layout(points) in;
layout(triangle_strip, max_vertices = 41) out;

uniform mat4 viewProjectionMatrix;
uniform vec2 scale;

in vec4 geomPosition[1];

const float PI02 = 0.3141593;

void main()
{
	vec4 center = viewProjectionMatrix*geomPosition[0];

	vec4 vertex = center;

	for (int i = 0; i <= 20; i++)
	{

		vertex.x = center.x + scale.x * sin(PI02 * i);
		vertex.y = center.y + scale.y * cos(PI02 * i);
		gl_Position = vertex;
		EmitVertex();

		gl_Position = center;
		EmitVertex();
	}
	EndPrimitive();
}